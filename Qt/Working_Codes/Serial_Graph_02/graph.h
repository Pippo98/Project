#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <QtCharts/QAbstractSeries>
#include <QtSerialPort/QSerialPort>
#include <QtCharts/QXYSeries>
#include <QtCharts/QLineSeries>
#include <QPointF>

QT_BEGIN_NAMESPACE
class QQuickView;
QT_END_NAMESPACE

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
    Q_INVOKABLE double get_y_max();
    Q_INVOKABLE double get_y_min();
    void upd(QString);

signals:
    void set_axisChanged();

public:
     QVector<double> y_arr;
     QList<QVector<QPointF>> points_list;
     QXYSeries *mSeries;
     double x;
     int max_points = 500;
     int max_indexes[2];
     int min_indexes[2];
};

#endif // GRAPH_H
