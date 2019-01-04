import QtQuick 2.0
import QtQuick.Controls 2.2
import QtCharts 2.0
import QtQuick.Layouts 1.3

ChartView {
    id: chartView
    anchors.fill: parent

    antialiasing: true
    theme: ChartView.ChartThemeQt
    backgroundRoundness: 10

    ValueAxis {
        id: axisY1
        min: 0
        max: 80
        visible: true
        tickCount: 7
        labelsAngle: -45
    }
    ValueAxis {
        id: axisY2
        min: 0
        max: 80
        visible: true
        gridVisible: false
        labelsAngle: -45
        tickCount: 7
    }
    ValueAxis {
        id: axisY3
        min: 0
        max: 80
        visible: true
        gridVisible: false
        labelsAngle: -45
        tickCount: 7
    }
    ValueAxis {
        id: axisY4
        min: 0
        max: 80
        visible: false
    }
    ValueAxis {
        id: axisY5
        min: 0
        max: 80
        visible: false
    }
    ValueAxis {
        id: axisY6
        min: 0
        max: 80
        visible: false
    }
    ValueAxis {
        id: axisY7
        min: 0
        max: 80
        visible: false
    }
    ValueAxis {
        id: axisY8
        min: 0
        max: 80
        visible: false
    }
    ValueAxis {
        id: axisY9
        min: 0
        max: 80
        visible: false
    }
    ValueAxis {
        id: axisY10
        min: 0
        max: 80
        visible: false
    }

    ValueAxis {
        id: axisX
        min: 0
        max: 1000
        gridVisible: false
    }

    LineSeries {
        id: lineSeries1
        name: "signal 1"
        color: "red"
        axisX: axisX
        axisY: axisY1
    }

    LineSeries {
        id: lineSeries2
        name: "signal 2"
        color: "green"
        axisX: axisX
        axisY: axisY2
    }
    LineSeries {
        id: lineSeries3
        name: "signal 3"
        color: "blue"
        axisX: axisX
        axisY: axisY3

    }
    LineSeries {
        id: lineSeries4
        name: "signal 4"
        color: "black"
        axisX: axisX
        axisY: axisY4

    }
    LineSeries {
        id: lineSeries5
        name: "signal 5"
        color: "black"
        axisX: axisX
        axisY: axisY5

    }
    LineSeries {
        id: lineSeries6
        name: "signal 6"
        color: "black"
        axisX: axisX
        axisY: axisY6
    }
    LineSeries {
        id: lineSeries7
        name: "signal 7"
        color: "black"
        axisX: axisX
        axisY: axisY7
    }
    LineSeries {
        id: lineSeries8
        name: "signal 8"
        color: "black"
        axisX: axisX
        axisY: axisY8
    }
    LineSeries {
        id: lineSeries9
        name: "signal 9"
        color: "black"
        axisX: axisX
        axisY: axisY9
    }
    LineSeries {
        id: lineSeries10
        name: "signal 10"
        color: "black"
        axisX: axisX
        axisY: axisY10
    }

    Timer {
        interval: 1 / 60 * 1000
        running: true
        repeat: true
        onTriggered: {
            for(var i = 0; i < 10; i++){
                graph.printCoord(chartView.series(i), i);
            }
            graph.getAxisValues(chartView.axisX(series(0)), 0, 0, 0)
        }
    }

    Timer{
        id: resizeTimer
        interval: 500
        running: true
        repeat: true
        onTriggered: {
            graph.setGeneralYRange()
            graph.setSpecificYRange()
            for(var i = 0; i < 10; i ++){
                graph.getAxisValues(chartView.axisY(series(i)), i, 1, 0);
            }
        }
    }
}
