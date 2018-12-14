#include <QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTextStream>
#include <QObject>
#include "serial.h"
#include "backend.h"
#include "graph.h"

static QByteArray serial_data;

QTimer *tim1 = new QTimer;
static Serial *ser = new Serial(nullptr);

static QTextStream out(stdout);

static Backend backend;
static Graph graph;

static bool done_calibration = false;

static QVector<double> arr;

Serial::Serial(QObject *parent) : QObject(parent){

}

QVector<double> Serial::get_val(){
    return arr;
}

void Serial::parseData(){

    QStringList number_arr;
    QByteArray number;

    for(int i = 0; i < serial_data.length(); i++){
        if(serial_data[i] != '\t' && serial_data[i] != '\n' && serial_data[i] != ' '){  //these are the separator from the different numbers in the received buffer
            number.append(serial_data[i]);
        }
        else{
            number_arr.append(number);
            number.clear();
        }
    }

    if(number_arr.length() == backend.total_graphs){            //if the numbers found in the received string are te same number ad the average found then do the cast fo float
        for(int i = 0; i < number_arr.length(); i++){
            if(arr.length() < number_arr.length()){
                arr.append(number_arr[i].toDouble());
            }
            else{
                arr[i] = number_arr[i].toDouble();
            }
        }
        //qDebug() << serial_data;
    }
    else{
        qDebug() << "wrong";
    }
}

QString * Serial::is_opened(){
//    graph.port_opened = is_port_opened;
    return &is_port_opened;
}

//initialization
//sometimes the read buffer iss not correct
//do an average of the numbers found in the firsts strings
//this average is the number of the graphs that can be visible in the chart
void Serial::detect_graphs(){

    int counter = 0;
    int iterations = 0;
    float average = 0;

    while(iterations < 20){
        for(int j = 0; j < serial_data.length(); j++){
            if(serial_data[j] == '\t' || serial_data[j] == '\n' || serial_data[j] == ' '){
                counter ++;
            }
        }
        average += counter;
        counter = 0;
        iterations ++;
    }
    average /= 20;

    //setting the variables
    backend.total_graphs = int(average);

    done_calibration = true;

    //disconnect because this function is only for initialization
    //QObject::disconnect(serial_port, &QSerialPort::readyRead, nullptr, nullptr);
}

//connectrion needed
void Serial::connection(){

    //connection to read the buffer
    QObject::connect(serial_port, &QSerialPort::readyRead, ser, [=]{
        serial_data = serial_port->readLine();
        //initialization to detect how many graphs need to be visualized
        if(!done_calibration)
            detect_graphs();
    });

    //timer to set the refresh rate of the plotting data
    tim1->setInterval(5);
    tim1->start();
    QObject::connect(tim1, &QTimer::timeout, [=]{
        parseData();
        clearSerial();
    });
}

//function to detect the available ports
//this is called fron the qml to set the combo box
QStringList Serial::detectPort(){
    const auto ser = QSerialPortInfo::availablePorts();
    QStringList port_list;
    port_list.append("      ");
    for(const QSerialPortInfo &ser_ : ser){
        port_list.append(ser_.portName());
    }

    serial_ports = port_list;

    return port_list;
}

void Serial::setDetectPort(QStringList value){
    serial_ports = value;
}

//function needed to clear all the unused data
void Serial::clearSerial(){
    serial_port->clear();
}

//simply opens the selected port from the qml
bool Serial::init(){

    bool result = false;
    serial_port = new QSerialPort();

    qDebug() << serial_port_selected;

    serial_port->setPortName(serial_port_selected);
    serial_port->setBaudRate(QSerialPort::Baud115200);
    serial_port->setDataBits(QSerialPort::Data8);
    serial_port->setFlowControl(QSerialPort::NoFlowControl);
    serial_port->setParity(QSerialPort::OddParity);

    if(serial_port->open(QSerialPort::ReadWrite)){
        result = true;
        graph.upd("O");
    }
    else{
        qDebug() << "Cannot Open Serial Port";
        result = false;
    }

    return result;
}

//disconnect everything and closes the serial port
void Serial::deInit(){

    QObject::disconnect(tim1, &QTimer::timeout, nullptr, nullptr);
    QObject::disconnect(serial_port, &QSerialPort::readyRead, nullptr, nullptr);

    graph.upd("C");

    serial_port->close();

    qDebug() << "Serial Port Closed";
}
