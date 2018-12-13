#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

class Backend : public QObject
{
    Q_OBJECT

public:
    explicit Backend(){}
    Backend(QObject *parent);

public:
    void principal();
    void init_graph();

public slots:
    void buttonClicked(int, int);
    void spingChanged(int, int);
    void comboChanged(QString, int);

public:
    int total_graphs;

};

#endif // BACKEND_H
