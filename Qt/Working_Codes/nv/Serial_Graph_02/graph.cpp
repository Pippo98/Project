#include <QDebug>
#include <QObject>
#include <QtCharts/QXYSeries>
#include <QtCharts/QLineSeries>
#include <QtSerialPort>
#include "graph.h"
#include "serial.h"
#include "backend.h"

//QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)

static Serial serial;
static Backend backend;

static QString port_opened;

Graph::Graph(QObject * parent) : QObject (parent)
{
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();

}

void Graph::upd(QString val){
    port_opened = val;
}

//this function updates the values of the line series in the qml
void Graph::print_coord(QAbstractSeries * series, int index){

    y_arr = serial.get_val();

    while(points_list.count() < 10){
        QVector<QPointF> points;
        points_list.append(points);
    }

    if(port_opened == "O" && y_arr.count() > 0){
        if(index < points_list.count() && index < y_arr.count()){
            if(series){
                if(index == 0){
                    x++;
                }
                points_list[index].append(QPointF(x, y_arr[index]));
                if(max_points < points_list[index].count()){
                    points_list[index].remove(0);
                }
                mSeries = static_cast<QXYSeries *>(series);
                mSeries->replace(points_list[index]);
                //set_axis();
            }
        }
    }
}

//this function calculates the max and min value in all the graphs
//it is a absolute max and min
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

//function that calculates the absolute min and max of a single graph
void Graph::get_axis(){
    for(int i = 0; i < points_list.count(); i ++){
        double max = -100000000;
        double min = 100000000;
        for (int j = 0; j < points_list.at(i).count(); j ++){
            if(points_list.at(i).at(j).y() > max){
                max = points_list.at(i).at(j).y();
                y_max_indexes[i] = j;
            }
            if(points_list.at(i).at(j).y() < min){
                min = points_list.at(i).at(j).y();
                y_min_indexes[i] = j;
            }
        }
    }
}

//this function communicates with qml
//sets the extremes of the two axis displayed in the chart
void Graph::get_axis_values(QAbstractAxis * axel, int index, int x_y, int single_total){
    if(index < points_list.count() && index < y_arr.count()){
        if(single_total == 0){
            if(x_y == 0){                                                           //X axis
                axel->setMin(points_list.at(0).at(0).x());
                axel->setMax(points_list.at(0).at(points_list.at(0).count()-1).x());
            }
            if(x_y == 1){                                                           //Y axis
                axel->setMin(points_list.at(index).at(y_min_indexes[index]).y());
                axel->setMax(points_list.at(index).at(y_max_indexes[index]).y());
            }
        }
        if(single_total == 1){
            if(x_y == 0){                                                           //X axis
                axel->setMin(points_list.at(0).at(0).x());
                axel->setMax(points_list.at(0).at(points_list.at(0).count()-1).x());
            }
            if(x_y == 1){                                                           //Y axis
                axel->setMin(points_list.at(min_indexes[0]).at(min_indexes[1]).y());
                axel->setMax(points_list.at(max_indexes[0]).at(max_indexes[1]).y());
            }
        }
    }
}














