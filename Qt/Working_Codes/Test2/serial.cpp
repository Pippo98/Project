#include "serial.h"
#include <QObject>
#include <QtDebug>
#include <QAbstractAxis>
#include <QValueAxis>
#include "string.h"

using namespace QtCharts;

static QByteArray serial_data;
static const char * pointer;
static char string[200];
static double x, y;
static int range = 600;
static int points = 0;

static QLineSeries *series;
static QChart *chart;
static QChartView *chartView;

static QList<int> a;

static QObject obj;

static QValueAxis *axisX;
static QValueAxis *axisY;

static int maxX = 50, maxY = 10;
static int x_scaler = 1;
static int y_scaler = 1;

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

    static Mine_Serial s;

    graph_init();

}

void Mine_Serial::graph_init(){
    //list  = new QList<QLineSeries>;

    series = new QLineSeries();
    chart = new QChart();
    axisX = new QValueAxis;
    axisY = new QValueAxis;

    QPen pen(Qt::red);
    pen.setWidth(1);
    series->setPen(pen);

    //chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTheme(QChart::ChartThemeDark);

    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Fucking Beautifull GRAPH");

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    Mine_Serial s;

    axisX->setRange(0, 100);
    axisY->setRange(0, 1);
    chart->setAxisX(axisX, series);
    chart->setAxisY(axisY, series);

    window.setCentralWidget(chartView);
    window.resize(1800, 600);
    window.show();

}

void Mine_Serial::init(){
    QObject::connect(serial, &QSerialPort::readyRead, [=]{
        serial_data = serial->readLine();
        Mine_Serial::get_coord();
    });
}

void Mine_Serial::get_coord(){

    if(strstr(serial_data, "start") || strstr(serial_data, "stop")){
        qDebug() << "Start";
        series->clear();
        x = 0;
        x_scaler = 1;
        y_scaler = 1;
        maxX = 50;
        maxY = 10;
    }

    if(strstr(serial_data, "y:")){
        x++;

        pointer = strstr(serial_data, "y:");

        strcpy(string, pointer);

        pointer += 2;

        y = atof(pointer);

        series->append(x, y);

        if(points > range){
            series->removePoints(0, 1);
        }
        else{
            points++;
        }

        maxX = int(x);
        axisX->setMax(maxX);
        axisX->setMin(maxX - range);

        if(y >= (maxY * 0.9)){
            y_scaler ++;
            maxY *= y_scaler;
            axisY->setRange(-maxY, maxY);
        }

        resize();

        window.update();
    }
}

void Mine_Serial::resize(){

}





