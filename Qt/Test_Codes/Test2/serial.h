#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include "QtSerialPort/QSerialPort"
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

class Mine_Serial : public QObject{

    Q_OBJECT

public:
    explicit Mine_Serial(){}

public:
    void serial_read();

    Mine_Serial(QObject *parent);

    void get_coord();

    void init();

private:
    QMainWindow window;

};

#endif
