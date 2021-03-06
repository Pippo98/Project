#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <QtCharts/QAbstractSeries>
#include <QtSerialPort/QSerialPort>
#include <QtCharts/QXYSeries>
#include <QtCharts/QLineSeries>
#include <QPointF>

QT_CHARTS_USE_NAMESPACE

class Graph : public QObject
{
    Q_OBJECT

public:
    explicit Graph(){}
    Graph(QObject *parent);

public:
    Q_INVOKABLE void print_coord(QAbstractSeries *, int);
    Q_INVOKABLE void set_axis();
    Q_INVOKABLE void get_axis_values(QAbstractAxis *, int, int, int);
    Q_INVOKABLE void get_axis();
    void upd(QString);

signals:
    void set_axisChanged();

public:
     QVector<double> y_arr;
     QList<QVector<QPointF>> points_list;
     QXYSeries *mSeries;
     double x;
     int max_points = 200;
     int max_indexes[2];
     int min_indexes[2];
     int y_max_indexes[100];
     int y_min_indexes[100];
     int total_graphs;
};

#endif // GRAPH_H
