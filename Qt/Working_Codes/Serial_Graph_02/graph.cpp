#include <QDebug>
#include <QtCharts/QXYSeries>
#include <QtCharts/QLineSeries>
#include <QtSerialPort>
#include "graph.h"
#include "serial.h"

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)

static Serial serial;

Graph::Graph(QObject * parent) : QObject (parent)
{
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();
}

void Graph::print_coord(QAbstractSeries * series, int index){

    y_arr = serial.get_val();
    if(serial.is_port_opened)
        qDebug() << "---";

    while(points_list.count() < 10){
        QVector<QPointF> points;
        points_list.append(points);
    }

    if(y_arr.length() > 0)
        x++;

    for(int i = 0; i < y_arr.count(); i++){
        if(max_points < points_list[i].count()){
            points_list[i].append(QPointF(x, y_arr[i]));
            points_list[i].removeFirst();
        }
        else{
            points_list[i].append(QPointF(x, y_arr[i]));
        }
    }

    if(index < points_list.count()){
        if(series){
            mSeries = static_cast<QXYSeries *>(series);
            mSeries->replace(points_list[index]);
        }
    }
}
