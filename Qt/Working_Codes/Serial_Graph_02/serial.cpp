#include <QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTextStream>
#include <QObject>
#include "serial.h"
#include "backend.h"
#include "graph.h"

static QSerialPort *serial_port;
static QByteArray serial_data;

static QTimer *tim1 = new QTimer();
static Serial *ser = new Serial(nullptr);

static QTextStream out(stdout);

static Backend backend;
static Graph graph;

static bool done_calibration = false;

QVector<double> arr;

//TODO: parse data, if dataa is not long as the others delete it

Serial::Serial(QObject *parent) : QObject(parent){

}

QVector<double> Serial::get_val(){
    return arr;
}

void Serial::parseData(){

    QStringList number_arr;
    QByteArray number;


    if(!done_calibration)
        detect_graphs();

    for(int i = 0; i < serial_data.length(); i++){
        if(serial_data[i] != '\t' && serial_data[i] != '\n' && serial_data[i] != ' '){
            number.append(serial_data[i]);
        }
        else{
            number_arr.append(number);
            number.clear();
        }
    }

    if(number_arr.length() == backend.total_graphs){

        for(int i = 0; i < number_arr.length(); i++){
            if(arr.length() < number_arr.length()){
                arr.append(number_arr[i].toDouble());
            }
            else{
                arr[i] = number_arr[i].toDouble();
            }
        }
        graph.set_val(arr);

    }
    else{
        qDebug() << "wrong";
    }


}

void Serial::detect_graphs(){

    int counter = 0;
    int iterations = 0;
    float average = 0;

    while(iterations < 10){
        for(int j = 0; j < serial_data.length(); j++){
            if(serial_data[j] == '\t' || serial_data[j] == '\n' || serial_data[j] == ' '){
                counter ++;
            }
        }
        average += counter;
        counter = 0;
        iterations ++;
    }
    average /= 10;

    backend.total_graphs = int(average);

    done_calibration = true;

    QObject::disconnect(serial_port, &QSerialPort::readyRead, nullptr, nullptr);

    //qDebug() << backend.total_graphs;
}

void Serial::connection(){

    QObject::connect(serial_port, &QSerialPort::readyRead, ser, [=]{
        serial_data = serial_port->readLine();
        detect_graphs();
    });

    tim1->setInterval(40);
    tim1->start();
    QObject::connect(tim1, &QTimer::timeout, [=]{
        parseData();
        clearSerial();
    });

    QObject::connect(serial_port, &QSerialPort::readyRead, ser, [=]{
        serial_data = serial_port->readLine();
    });
}

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

void Serial::clearSerial(){
    serial_port->clear();
}

bool Serial::init(){

    bool result = false;
    serial_port = new QSerialPort();

    qDebug() << serial_port_selected;

    serial_port->setPortName(serial_port_selected);
    serial_port->setBaudRate(QSerialPort::Baud115200);
    serial_port->setDataBits(QSerialPort::Data8);
    serial_port->setFlowControl(QSerialPort::NoFlowControl);
    serial_port->setParity(QSerialPort::NoParity);

    if(serial_port->open(QSerialPort::ReadWrite)){
        result = true;
    }
    else{
        qDebug() << "Cannot Open Serial Port";
        result = false;
    }

    //connection();

    return result;
}

bool Serial::deInit(){

    QObject::disconnect(tim1, &QTimer::timeout, nullptr, nullptr);
    QObject::disconnect(serial_port, &QSerialPort::readyRead, nullptr, nullptr);

    serial_port->close();

    qDebug() << "Serial Port Closed";

    return true;
}
