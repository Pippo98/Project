#include "mainwindow.h"
#include "serial.h"
#include <QApplication>
#include <QtQml/QQmlContext>
/*
#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlContext>*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Mine_Serial s(0);

    return a.exec();
}
