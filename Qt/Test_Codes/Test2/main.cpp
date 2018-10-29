#include "mainwindow.h"
#include "serial.h"
#include <QApplication>
/*
#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlContext>*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QQuickView *view = new QQuickView;

    Mine_Serial s(0);

    //view->engine()->rootContext()->setContextProperty("Serial", &s);

    //s.init();

    return a.exec();
}
