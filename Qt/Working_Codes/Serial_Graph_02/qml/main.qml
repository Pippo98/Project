import QtQuick 2.9
import QtCharts 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.0
import com.serial 1.0
import com.graph  1.0

ApplicationWindow {
    id: root
    visible: true
    width: 980
    height: 480
    color: "#424347"
    opacity: 1
    title: "Multi Graph Plotter"
    //property alias Buttons: buttons

    Graph_qml{
        id: graph_qml
    }

    ControlPanel{
        id: controlPanel

        objectName: "controlPanelObj"

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 10
        anchors.leftMargin: 10
        height: parent.height / 2
    }

    GraphChart{
        id: graph1
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: controlPanel.right
    }
}
