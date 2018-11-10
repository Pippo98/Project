#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include "QtSerialPort/QSerialPort"
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QAbstractAxis>

class Mine_Serial : public QObject{

    Q_OBJECT

public:
    explicit Mine_Serial(){}

public:
    Mine_Serial(QObject *parent);

    void serial_read();

    void graph_init();

    void get_coord();

    void init();

    void resize();

private:
    QMainWindow window;

};

#endif
