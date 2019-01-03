import QtQuick 2.0

Item {
    id: root

    property double min: 0
    property double max: 1000
    property double value: 50
    property double barWidth: 150
    //property string textMin: (min)
    //property string textMax: string(max)

    Text{
        id: valueText
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        color: "white"
        text: value
    }

    Text{
        id: t1
        text: min
        color: "white"
        anchors.top: valueText.bottom
        anchors.verticalCenter: parent.verticalCenter
    }


    Rectangle{
        id: bar
        color: "white"
        anchors.left: t1.right
        //anchors.verticalCenter: parent.verticalCenter
        anchors.bottom: parent.bottom
        width: root.width
        height: 2
        Rectangle{
            id: perc
            //anchors.verticalCenter: parent.verticalCenter
            anchors.bottom: parent.bottom
            //anchors.left: parent.left
            //anchors.right: parent.right
            width: (value / (max - min)) * root.width
            height: 10
            color: "red"
            radius: height / 5
        }
    }

    Timer{
        interval: 200
        running: true
        repeat: true
        onTriggered: {
            value = value + 5
        }
    }

    Text{
        id: t2
        text: max
        color: "white"
        anchors.left: bar.right
        anchors.verticalCenter: parent.verticalCenter
    }
}
