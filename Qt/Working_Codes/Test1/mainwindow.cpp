#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtSerialPort/QSerialPort"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

static QSerialPort *serial;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial = new QSerialPort(this);

    connect(serial, SIGNAL(readyRead()), this, SLOT(serial_received()));

    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);
}

static char txt[100];
//QByteArray serial_data;
static QByteArray serial_data;

void MainWindow::serial_received()
{
    ui->textEdit->setReadOnly(true);

    //qDebug(serial->read(100));
    serial_data =serial->readLine(100);
    serial_actions();

    if(!ui->textEdit->underMouse()){
        ui->textEdit->setText(serial_data);
    }
}

void MainWindow::serial_actions(){
    if(strstr(serial_data, "led1 on")){
        ui->radioButton->setChecked(true);
    }
    else if(strstr(serial_data, "led1 off")){
        ui->radioButton->setChecked(false);
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->pushButton->text() == "Open Port"){
        serial->setPortName("/dev/ttyACM1");
        serial->setBaudRate(QSerialPort::Baud115200);
        serial->setDataBits(QSerialPort::Data8);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        serial->setParity(QSerialPort::NoParity);

        if(serial->open(QSerialPort::ReadWrite) == true){
            ui->lineEdit->setText("ACM1 opened");
        }
        else{
            ui->lineEdit->adjustSize();
            serial->setPortName("/dev/ttyACM2");
            if(serial->open(QSerialPort::ReadWrite) == true){
                ui->lineEdit->setText("ACM2 opened");
            }
            else{
                ui->lineEdit->adjustSize();
                serial->setPortName("/dev/ttyACM3");
                if(serial->open(QSerialPort::ReadWrite) == true){
                    ui->lineEdit->setText("ACM2 opened");

                }
                else{
                    ui->lineEdit->setText("failed to open serial port");
                }
            }
        }
    }
    else{
        if(ui->pushButton->text() == "Close Port"){
            serial->close();
            ui->pushButton->setText("Open Port");
            ui->lineEdit->setText("Serial Port Closed");
        }
    }
    if(serial->isOpen() == true){
        ui->pushButton->setText("Close Port");
    }
}

MainWindow::~MainWindow()
{
    if(serial->isOpen())
        serial->close();
    delete serial;
    delete ui;
}

void MainWindow::on_radioButton_clicked(bool checked)
{

    if(checked){
        serial->write("set l1 on\r\n");
    }
    else{
        serial->write("set l1 off\r\n");
    }
}
