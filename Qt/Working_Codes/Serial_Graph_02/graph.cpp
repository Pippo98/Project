#include <QDebug>
#include <QtCharts/QXYSeries>
#include <QtCharts/QLineSeries>
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

    //qDebug() << "print_coord";
    y_arr = serial.get_val();

    while(points_list.count() < 10){
        points_list.append(points);
    }

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
            //points.append(QPointF(x, 15));
            mSeries = static_cast<QXYSeries *>(series);
            mSeries->replace(points_list[index]);
        }
    }

    //qDebug() << points_list[0];

    if(y_arr.count() > 0){
        x ++;
    }

    //emit vValueChanged();
}

void Graph::set_val(QVector<double> val){
        y_arr = val;
}

void Graph::set_graph_series(QAbstractSeries *series){
    qDebug() << "set_graph_series";
    /*
    if(series)
        mSeries = static_cast<QXYSeries *>(series);*/
}

void Graph::update(QAbstractSeries *series){
/*
    if(points_list.count() > 0){
        mSeries = static_cast<QXYSeries *>(series);
        mSeries->replace(points_list[0]);
    }*/
    qDebug() << "update";
    if(points.count() > 0 && series){
        mSeries = static_cast<QXYSeries *>(series);
        mSeries->replace(points);
    }
}
