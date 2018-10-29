#include "serial.h"
#include <QObject>
#include <QtDebug>
#include <QAbstractAxis>
#include <QValueAxis>

using namespace QtCharts;

static QByteArray serial_data;
static const char * pointer;
static double x, y;

static QLineSeries *series;
static QChart *chart;
static QChartView *chartView;

static QObject obj;

static QValueAxis *axisX;
static QValueAxis *axisY;

static int maxX = 50, maxY = 10;
static int x_scaler = 1;
static int y_scaler = 1;
static char data_buffer[100];

static QSerialPort *serial;

Mine_Serial::Mine_Serial(QObject *parent) : QObject(parent){

    serial = new QSerialPort();
    qDebug() << "init";
    Mine_Serial::init();
    qDebug() << "init done";

    serial->setPortName("/dev/ttyACM1");
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setParity(QSerialPort::NoParity);

    if(serial->open(QSerialPort::ReadWrite) == true){
        //acm1 opened
        qDebug() << "ACM1 opened";
    }
    else{
        serial->setPortName("/dev/ttyACM2");
        if(serial->open(QSerialPort::ReadWrite) == true){
            qDebug() << "ACM2 opened";
            //acm2 opened
        }
        else{
            serial->setPortName("/dev/ttyACM3");
            if(serial->open(QSerialPort::ReadWrite) == true){
                qDebug() << "ACM3 opened";
                //acm3 opened

            }
            else{
                qDebug() << "Failed to Open Serial Port";
                //failed to open port
            }
        }
    }

    series = new QLineSeries();
    chart = new QChart();
    axisX = new QValueAxis;
    axisY = new QValueAxis;
    chartView = new QChartView(chart);

    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Fucking Beautifull GRAPH");

    chartView->setRenderHint(QPainter::Antialiasing);

    Mine_Serial s;

    axisX->setRange(0, 100);
    axisY->setRange(0, 100);
    chart->setAxisX(axisX, series);
    chart->setAxisY(axisY, series);

    window.setCentralWidget(chartView);
    window.resize(1800, 600);
    window.show();
}

void Mine_Serial::serial_read(){
    //qDebug(serial->read(100));
    serial_data = serial->readLine(1000);
    static Mine_Serial s;
    s.get_coord();
}

void Mine_Serial::init(){
    QObject::connect(serial, &QSerialPort::readyRead, [=]{
        serial_data = serial->readLine(1000);
        Mine_Serial::get_coord();
    });
}

void Mine_Serial::get_coord(){

    if(strstr(serial_data, "x:") && strstr(serial_data, "y:")){
        x++;
        pointer = strstr(serial_data, "x:");
        pointer += 2;
        qDebug() << pointer;
        y = atof(pointer);
        pointer = strstr(serial_data, "y:");
        pointer += 2;
        //y = atof(pointer);
        series->append(x, y);

        if(x >= (maxX * 0.9)){
            x_scaler ++;
            maxX *= x_scaler;
            //axisX->setRange(0, maxX);
            axisX->setMax(maxX);
            //chart->setAxisX(axisX, series);
        }
        if(y >= (maxY * 0.9)){
            y_scaler ++;
            maxY *= y_scaler;
            axisY->setRange(0, maxY);
            //axisY->setRange(0, 1000);
            //chart->setAxisY(axisY, series);
        }
        window.update();
    }
}
