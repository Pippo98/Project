import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    width: 600
    height: 400

    header: Label {
        text: qsTr("Terminal")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Connections{
        target: serial
        onDataChanged:{
            textArea.text = data
            console.log("qml slot")
        }
    }

    TextArea {
        id: textArea
        //property string txt
        enabled: true
        font.family: "Source Code Pro"
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }
}
