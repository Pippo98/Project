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
    QVector<double> getPointsData();
    bool isSerialOpened();

    void setText();
    void setPrint_data(QString);
    QString print_data();

    void setLogState(bool);

    void parseCan();

signals:
    void print_dataChanged();
    void dataChanged(QString data);
    //void dataChanged();
    void graphsChanged(int number);
    void portStateChanged(int state);

public slots:
    void manageData();
    QString portInfo(QString port);
    QStringList detectPort();
    QString getText();

public:
    int baudRateSelected;
    int serialPortIndex;

    QString serialPortSelected;
    QSerialPort * serialPort;
    QStringList serialPorts;
    QByteArray serialData;

};

#endif // SERIAL_H
