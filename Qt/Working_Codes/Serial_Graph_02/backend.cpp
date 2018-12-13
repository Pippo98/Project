#include "backend.h"
#include "serial.h"
#include <QDebug>

static Serial s;

Backend::Backend(QObject *parent) : QObject(parent){

}
void Backend::comboChanged(QString active_member, int index){
    s.serial_port_index = index;
    s.serial_port_selected = active_member;
}

void Backend::buttonClicked(int id, int value){
    switch (id) {
    case 0:
        if(value == 0){
            s.init();
            s.connection();
        }
        else{
            s.deInit();
        }
        break;

    case 1:
        break;

    default:
        break;

    }
}

void Backend::spingChanged(int id, int value){

}


