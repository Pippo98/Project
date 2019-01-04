#include "graph.h"
#include "serial.h"
#include "backend.h"

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

static QTimer *tim1 = new QTimer();
static QFile *fil = new QFile();

static serial *s = new serial;
const auto ser = QSerialPortInfo::availablePorts();
static graph g;
static backend b;

static bool CAN_MODE = true;

static bool doneCalibration = false;
static int iterations = 0;
static double average = 0;
static bool isPortOpened;

static QString text;

static QVector<double> dataArray;
static QVector<double> canArr;

static bool logState = false;

struct frontalStc{
    double encoder1;
    double encoder2;
    double steer;
    double gx;
    double gy;
    double gz;
    double ax;
    double ay;
    double az;
};

struct pedalsStc{
    double brk;
    double apps1;
    double apps2;
};

struct ecuStc{

};

struct inverterStc{

};

struct lvAccumulatorStc{

};

struct hvAccumulatorStc{

};

static struct frontalStc       frontal;
static struct pedalsStc        pedals;
static struct ecuStc           ecu;
static struct inverterStc      inverter;
static struct lvAccumulatorStc lvAccumulator;
static struct hvAccumulatorStc hvAccumulator;

serial::serial(QObject * parent) : QObject (parent)
{
}
serial::~serial(){
    if(fil->isOpen())
    fil->close();
}

void serial::setLogState(bool state){
    logState = state;
    if(logState){
        QByteArray intestation;

        intestation.append("Eagle Trento Racing Team\r\n");
        intestation.append("Real Time Log File\r\n");
        intestation.append(QDateTime::currentDateTime().date().toString());
        intestation.append("\t");
        intestation.append(QDateTime::currentDateTime().time().toString());
        intestation.append("\r\n");

        QDir dir;
        dir.setCurrent("/home/filippo/Scrivania/logFolder");
        fil->setFileName("log" +
                         QDateTime::currentDateTime().date().toString()
                         + " " +
                         QDateTime::currentDateTime().time().toString()
                         );
        fil->open(QFile::ReadWrite);
        fil->write(intestation);
    }
    else{
        fil->close();
    }
}

void serial::parseCan(){
    if(dataArray.count() >= 8){
        //PEADLS
        if(int(dataArray[1]) == 176){
            if(int(dataArray[2]) == 1){
                pedals.apps1 = dataArray[3];
                pedals.apps2 = dataArray[4];
            }
            if(int(dataArray[2]) == 2){
                pedals.brk = dataArray[3];
            }
        }
        //FRONTAL
        if(int(dataArray[1]) == 192){
            if(int(dataArray[2]) == 2){
                frontal.steer = dataArray[3];
            }
        }
        if(int(dataArray[1]) == 208){
            if(int(dataArray[2]) == 6){
                frontal.encoder1 = dataArray[3];
            }
            if(int(dataArray[2]) == 7){
                frontal.encoder2 = dataArray[3];
            }
        }
    }
    canArr.clear();
    //FRONTAL
    if(b.getRequestedGraphs().at(0) == 1){
        //canArr.append(frontal.encoder1);
        //canArr.append(frontal.encoder2);
        canArr.append(frontal.ax);
        canArr.append(frontal.ay);
        canArr.append(frontal.az);
        canArr.append(frontal.gx);
        canArr.append(frontal.gy);
        canArr.append(frontal.gz);
        canArr.append(frontal.steer);
    }
    //PEDALS
    if(b.getRequestedGraphs().at(1) == 1){
        canArr.append(pedals.apps1);
        canArr.append(pedals.apps2);
        canArr.append(pedals.brk);
    }
    //ECU
    if(b.getRequestedGraphs().at(2) == 1){

    }
    //INVERTER
    if(b.getRequestedGraphs().at(3) == 1){

    }
    //LOW VOLTAGE
    if(b.getRequestedGraphs().at(4) == 1){

    }
    //HIGH VOLTAGE
    if(b.getRequestedGraphs().at(6) == 1){

    }
}

void serial::parseData(){

    QStringList numberArr;
    QByteArray number;
    QChar byte;

    for(int i = 0; i < serialData.count(); i++){
        byte = QChar(serialData[i]);
        if(byte != '\t' && byte != '\n'){  //these are the separator from the different numbers in the received buffer
            number.append(byte);
        }
        else{
            numberArr.append(number);
            number.clear();
        }
    }

    if(numberArr.length() == g.totalGraphs || CAN_MODE){            //if the numbers found in the received string are te same number ad the average found then do the cast fo float
        for(int i = 0; i < numberArr.length(); i++){
            if(dataArray.length() < numberArr.length()){
                dataArray.append(numberArr[i].toDouble());
            }
            else{
                dataArray.replace(i, numberArr[i].toDouble());
            }
        }
    }
    else{
        qDebug() << "wrong";
    }

}

void serial::manageData(){
    if(!doneCalibration && !CAN_MODE){
        detectGraphs();
    }
    if(doneCalibration || CAN_MODE){
        parseData();

        if(CAN_MODE){
        parseCan();
        }

        g.managePoints();

        if(logState)
        fil->write(serialData);
    }
}

//initialization
//sometimes the read buffer iss not correct
//do an average of the numbers found in the firsts strings
//this average is the number of the graphs that can be visible in the chart
void serial::detectGraphs(){
    int counter = 0;

    for(int j = 0; j < serialData.length(); j++){
        if(serialData[j] == '\t' || serialData[j] == '\n'){
            counter ++;
        }
    }
    average += counter;
    if(iterations == 19){
        average /= 20;
        average = round(average);
        g.totalGraphs = int(average);
        doneCalibration = true;
    }
    iterations ++;
}

//function to detect the available ports
//this is called fron the qml to set the combo box
QStringList serial::detectPort(){
    QStringList port_list;

    port_list.append("      ");

    for(const QSerialPortInfo &ser_ : ser)    {
        port_list.append(ser_.portName());
    }

    serialPorts = port_list;

    return port_list;
}

QString serial::portInfo(QString port){
    QString info;
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    for(int i = 0; i < serialPortInfos.count(); i++) {
        if(serialPortInfos.at(i).portName() == port){
            const QSerialPortInfo &serialPortInfo = serialPortInfos.at(i);
            info.append(serialPortInfo.description());
            info.append("\r\n");
            info.append(serialPortInfo.manufacturer());
        }
    }

    return info;
}

//connection needed
void serial::connection(){
    //connection to read the buffer
    connect(serialPort, &QSerialPort::readyRead, s, [=]{
        serialData = serialPort->readLine();
        manageData();
    });
}

bool serial::init(){

    bool result = false;
    serialPort = new QSerialPort();

    qDebug() << serialPortSelected;

    serialPort->setPortName(serialPortSelected);
    serialPort->setBaudRate(250000);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    serialPort->setParity(QSerialPort::NoParity);

    if(serialPort->open(QSerialPort::ReadOnly)){
        result = true;
        isPortOpened = true;
    }
    else{
        qDebug() << "Cannot Open Serial Port";
        result = false;
    }

    return result;
}

//disconnect everything and closes the serial port
void serial::deInit(){

    QObject::disconnect(serialPort, &QSerialPort::readyRead, nullptr, nullptr);

    isPortOpened = false;
    doneCalibration = false;
    iterations = 0;
    average = 0;

    serialPort->close();
    emit portStateChanged(0);

    qDebug() << "Serial Port Closed";
}

QString serial::print_data(){
    return text;
}

bool serial::isSerialOpened(){
    return isPortOpened;
}

QVector<double> serial::getPointsData(){
    if(CAN_MODE == true){
        return canArr;
    }
    else{
        return dataArray;
    }
}

void serial::setText(){
    text.append(serialData);

    if(text.size() > 500){
        text.remove(0, serialData.count());
    }
}

QString serial::getText(){
    return text;
}

void serial::setPrint_data(QString var){
    Q_UNUSED(var)
}















