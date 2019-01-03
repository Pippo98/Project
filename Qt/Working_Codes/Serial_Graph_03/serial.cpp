#include "graph.h"
#include "serial.h"
#include "backend.h"

#include <QDebug>
#include <QTimer>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

static QTimer *tim1 = new QTimer();

static serial *ser = new serial;
static graph g;

static bool doneCalibration = false;
static int iterations = 0;
static double average = 0;
static bool isPortOpened;

static QString text;

static QVector<double> dataArray;

typedef struct{
    double steer;
    double enc1;
    double enc2;
    double gx;
    double gy;
    double gz;
    double ax;
    double ay;
    double az;
}frontalStc;

typedef struct{
    double brk;
    double apps1;
    double apps2;
}pedalsStc;

typedef struct{

}ecuStc;

typedef struct{

}inverterStc;

typedef struct{

}lvAccumulatorStc;

typedef struct{

}hvAccumulatorStc;

static frontalStc       frontal;
static pedalsStc        pedals;
static ecuStc           ecu;
static inverterStc      inverter;
static lvAccumulatorStc lvAccumulator;
static hvAccumulatorStc hvAccumulator;

serial::serial(QObject * parent) : QObject (parent)
{
}
serial::~serial(){}

QVector<double> serial::getCan(){
    canArr.clear();
    canArr.append(pedals.apps1);
    canArr.append(pedals.apps2);
    canArr.append(pedals.brk);

    canArr.append(frontal.enc1);
    canArr.append(frontal.enc2);
    canArr.append(frontal.ax);
    canArr.append(frontal.ay);
    canArr.append(frontal.az);
    canArr.append(frontal.gx);
    canArr.append(frontal.gy);
    canArr.append(frontal.gz);
    canArr.append(frontal.steer);

    //canArr.append(ecu.);
    qDebug() << canArr;
    return canArr;
}

void serial::parseCan(){
    if(dataArray.count() >= 8){
        if(int(dataArray[1]) == 176){         //PEADLS
            if(int(dataArray[2]) == 1){
                pedals.apps1 = dataArray[3];
                pedals.apps2 = dataArray[4];
            }
            if(int(dataArray[2]) == 2){
                pedals.brk = dataArray[3];
            }
        }
        if(int(dataArray[1]) == 192){         //FRONTAL
            if(int(dataArray[2]) == 2){
                frontal.steer = dataArray[3];
            }
        }
        if(int(dataArray[1]) == 208){
            if(int(dataArray[2]) == 6){
                frontal.enc1 = dataArray[3];
            }
        }
    }
}

void serial::parseData(){

    QStringList numberArr;
    QByteArray number;
    QChar byte;

    for(int i = 0; i < serialData.length(); i++){
        byte = QChar(serialData[i]);
        if(byte != '\t' && byte != '\n'){  //these are the separator from the different numbers in the received buffer
            number.append(byte);
        }
        else{
            numberArr.append(number);
            number.clear();
        }
    }

    if(numberArr.length() == g.totalGraphs){            //if the numbers found in the received string are te same number ad the average found then do the cast fo float
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

void serial::getText(){
    text.append(serialData);

    if(text.size() > 5000){
        text.remove(0, serialData.count());
    }
}

void serial::manageData(){
    if(!doneCalibration){
        detectGraphs();
    }
    if(doneCalibration){
        parseData();
        getText();
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
    const auto ser = QSerialPortInfo::availablePorts();
    QStringList port_list;

    port_list.append("      ");

    for(const QSerialPortInfo &ser_ : ser)    {
        port_list.append(ser_.portName());
    }

    serialPorts = port_list;

    //emit dataChanged(text);

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
    connect(serialPort, &QSerialPort::readyRead, ser, [=]{
        //emit dataChanged(text);
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
    //serialPort->setBaudRate(250000);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    serialPort->setParity(QSerialPort::NoParity);

    if(serialPort->open(QSerialPort::ReadWrite)){
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

QVector<double> serial::getVal(){
    return dataArray;
}

bool serial::isSerialOpened(){
    return isPortOpened;
}

void serial::setPrint_data(QString var){
    Q_UNUSED(var)
}

void serial::setText(QString val){
    Q_UNUSED(val);
}
















