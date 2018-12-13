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
static QString port_opened;

Graph::Graph(QObject * parent) : QObject (parent)
{
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();

}

void Graph::upd(QString val){
    port_opened = val;
}

void Graph::print_coord(QAbstractSeries * series, int index){

    y_arr = serial.get_val();

    while(points_list.count() < 10){
        QVector<QPointF> points;
        points_list.append(points);
    }

    if(port_opened == "O"){
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
                //set_axis();
            }
        }
    }
}

void Graph::set_axis(){
    double max = -100000000;
    double min = 100000000;
    QVector<QPointF> points;

    for(int i = 0; i < points_list.length(); i++){
        for(int j = 0; j < points_list[i].length(); j ++){
            points = points_list[i];
            if(points.at(j).y() > max){
                max = points.at(j).y();
                max_indexes[0] = i;
                max_indexes[1] = j;
            }
            if(points.at(j).y() < min){
                min = points.at(j).y();
                min_indexes[0] = i;
                min_indexes[1] = j;
            }
        }
    }
}

double Graph::get_y_max(){
    if(points_list.at(0).count() >= 1){
        return points_list.at(max_indexes[0]).at(max_indexes[1]).y();
    }
    else{
        return 10;
    }
}

double Graph::get_y_min(){
    if(points_list.at(0).count() >= 1){
        return points_list.at(min_indexes[0]).at(min_indexes[1]).y();
    }
    else{
        return 0;
    }
}
















