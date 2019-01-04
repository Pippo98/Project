import QtQuick 2.0

Item {
    id: root

    property double min: 0
    property double max: 1000
    property double value: 50
    property double barWidth: 150
    //property string textMin: (min)
    //property string textMax: string(max)

    Grid{
        columns: 3
        rows: 2
        Text{
            id: valueText
            color: "white"
            text: value
        }

        Text{
            id: t1
            text: min
            color: "white"
        }

        Rectangle{
            id: bar
            color: "white"
            width: root.width
            height: 2
            Rectangle{
                id: perc
                //anchors.verticalCenter: parent.verticalCenter
                //anchors.left: parent.left
                //anchors.right: parent.right
                width: (value / (max - min)) * root.width
                height: 10
                color: "red"
                radius: height / 5
            }
        }

        Text{
            id: t2
            text: max
            color: "white"
        }
    }
}
