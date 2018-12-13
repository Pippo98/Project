#ifndef SERIAL_H
#define SERIAL_H

#include <QtSerialPort>
#include <QObject>

class Serial : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList detectPort READ detectPort WRITE setDetectPort NOTIFY detectPortChanged)

public:
    explicit Serial(){}
    Serial(QObject *parent);
    //~Serial();

public:
    void connection();
    bool init();
    bool deInit();
    void parseData();
    QStringList detectPort();
    void setDetectPort(QStringList);
    void detect_graphs();
    QVector<double> get_val();

signals:
    void detectPortChanged();

public slots:
    void clearSerial();

public:
    QStringList serial_ports;
    QString serial_port_selected;
    int serial_port_index;

};

#endif // SERIAL_H
