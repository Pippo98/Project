#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWidgets/QApplication>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QtCore/QDir>

#include "backend.h"
#include "serial.h"
#include "graph.h"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    Backend backend_;
    Graph graph_;
    Serial serial_;

    QQmlApplicationEngine engine;
    qmlRegisterType<Serial>("com.serial", 1, 0, "Serial_qml");
    qmlRegisterType<Graph>("com.graph", 1, 0, "Graph_qml");
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    engine.rootContext()->setContextProperty("backend", &backend_);
    engine.rootContext()->setContextProperty("graph", &graph_);
    engine.rootContext()->setContextProperty("serial", &serial_);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
