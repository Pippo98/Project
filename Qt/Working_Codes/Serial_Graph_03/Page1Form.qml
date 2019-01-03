import QtQuick 2.11
import QtCharts 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4
import QtQuick.Controls.Styles 1.4

Page {
    id: page
    width: 600
    height: 400

    header: Label {
        text: qsTr("Control Panel")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }
/*
    Connections{
        target: backend
        onPortStateChanged: {
            if(state == 0){
                switchColumn.stateVisible = false
            }
            else{
                switchColumn.stateVisible = true
            }
        }
    }*/

    Connections{
        target: serial
        onGraphsChanged:{
            switchColumn.members = number
        }
    }

    ControlPanel{
        id: controlPanel
        width: 145
        height: 343
        anchors.top: parent.top
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 0
    }


    ColumnLayout{
        id: switchColumn
        anchors.left: controlPanel.right
        anchors.top : parent.top
        property bool stateVisible: false
        property int members: 10
        spacing: 1
        //visible: stateVisible
        /*
        Bars{
            width: 150
        }*/

        Repeater{
            model: switchColumn.members
            Switch {
                text: "Graph " + index
                checked: true
                onCheckedChanged: {
                    backend.switchCanged(index, checked)
                }
            }
        }
    }
}
