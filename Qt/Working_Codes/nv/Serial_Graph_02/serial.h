#ifndef SERIAL_H
#define SERIAL_H

#include <QtSerialPort>
#include <QObject>

class Serial : public QObject
{
    Q_OBJECT

    //property called from the qml to setup the combo box
    Q_PROPERTY(QStringList detectPort READ detectPort WRITE setDetectPort NOTIFY detectPortChanged)

public:
    explicit Serial(){}
    Serial(QObject *parent);
    //~Serial();

public:
    void connection();
    bool init();
    void deInit();
    void parseData();
    QStringList detectPort();
    void setDetectPort(QStringList);
    void detect_graphs();
    QVector<double> get_val();
    Q_INVOKABLE QString * is_opened();

signals:
    void detectPortChanged();

public slots:
    void clearSerial();

public:
    QStringList serial_ports;
    QString serial_port_selected;
    int serial_port_index;
    QSerialPort * serial_port;
    QString is_port_opened;

};

#endif // SERIAL_H
