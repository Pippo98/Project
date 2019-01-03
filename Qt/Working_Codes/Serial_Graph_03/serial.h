#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QVector>

#include "backend.h"

class serial : public QObject
{
    Q_OBJECT
public:
    explicit serial(QObject *parent = nullptr);
    //explicit serial();
    ~serial();

    //Q_PROPERTY(QString getText READ getText WRITE setText)
    Q_PROPERTY(QString print_data READ print_data WRITE setPrint_data NOTIFY print_dataChanged)

    bool init();
    void deInit();
    void connection();
    void detectGraphs();
    void parseData();
    QVector<double> getVal();
    bool isSerialOpened();

    void setText(QString);
    void getText();
    void setPrint_data(QString);
    QString print_data();

    void parseCan();
    QVector<double> getCan();

signals:
    void print_dataChanged();
    void dataChanged(QString data);
    void graphsChanged(int number);
    void portStateChanged(int state);

public slots:
    void manageData();
    QString portInfo(QString port);
    QStringList detectPort();
    //QString getText();

public:
    int baudRateSelected;
    int serialPortIndex;

    QString serialPortSelected;
    QSerialPort * serialPort;
    QStringList serialPorts;
    QByteArray serialData;

    QVector<double> canArr;

};

#endif // SERIAL_H
