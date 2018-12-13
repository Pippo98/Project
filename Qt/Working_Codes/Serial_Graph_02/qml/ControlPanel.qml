import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import com.serial 1.0

ColumnLayout {

    id: controlPanel
    spacing: 2
    Layout.fillHeight: false

    Serial_qml {
        id: serial_qml
    }

    Text {
       id: columnTitle
       color: "red"
       opacity: 0.7
       font.pointSize: 24
       font.family: "Source Code Pro"
       text: qsTr("Menu")
    }

    Combo{

        id: combo1
        objectName: "combo1"
        members: serial_qml.detectPort

    }

    Buttons{
        id: btn1
        text: "Serial: "
        items: ["Opened", "Closed"]
        currentSelection: 1
        identifier: 0
    }
/*
    Text {
        id: graphsText
        color: "white"
        opacity: 0.9
        font.pointSize: 10
        font.family: "Source Code Pro"
        anchors.topMargin: 10
        text: qsTr("Graphs: ")

       Spin {
           id: spin1
           anchors.left: graphsText.right
           anchors.centerIn: graphsText.Center

           identifier: 0

           minimum: 0
           maximum: 10
       }
    }*/

    GraphPanel{
        id: graphPanel1
    }

}
