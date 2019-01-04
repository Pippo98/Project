#include "backend.h"
#include "serial.h"
#include "graph.h"

static serial s;
static graph  g;

static QVector<int> requestedGraphs;
static bool logEnabled = false;

backend::backend(QObject *parent) : QObject(parent)
{
}

void backend::comboChanged(QString active_member, int index, int identifier){
    switch (identifier) {
    case 0:
        s.serialPortIndex = index;
        s.serialPortSelected = active_member;
        break;
    }
}

void backend::buttonClicked(int id, int value){
    switch (id) {
    case 0:
        if(value == 0){
            s.init();
            s.connection();
            g.connection();
            emit portStateChanged(1);
        }
        else{
            s.deInit();
            g.deInit();
            emit portStateChanged(0);
        }
        break;
    default:
        break;

    }
}

void backend::logSwitchChanged(int value){
    if(value == 1){
        logEnabled = true;
    }
    else{
        logEnabled = false;
    }

    s.setLogState(logEnabled);
}

void backend::switchChanged(int id, int value){

    while(requestedGraphs.count() <= id){
        requestedGraphs.append(1);
    }
    requestedGraphs[id] = value;

    switch(id){
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    }
}

QVector<int> backend::getRequestedGraphs(){
    return requestedGraphs;
}
