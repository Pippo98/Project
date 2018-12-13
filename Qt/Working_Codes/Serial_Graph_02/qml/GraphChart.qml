import QtQuick 2.0
import QtCharts 2.2
import com.serial 1.0
import com.graph 1.0

ChartView {
    id: chartView

    antialiasing: true
    theme: ChartView.ChartThemeQt
    //backgroundColor: "#525357"
    //backgroundColor: "#00ff00"
    backgroundRoundness: 0
    property var points_number: 1000

    Graph_qml{
        id: graph_qml
    }

    ValueAxis {
        id: axisY1
        min: 20
        max: 80
    }

    ValueAxis {
        id: axisY2
        min: 0
        max: 500
    }

    ValueAxis {
        id: axisX
        min: 0
        max: 5000
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
        axisY: axisY1
    }
    LineSeries {
        id: lineSeries3
        name: "signal 3"
        color: "blue"
        axisX: axisX
        axisY: axisY1
    }
    LineSeries {
        id: lineSeries4
        name: "signal 4"
        color: "black"
        axisX: axisX
        axisY: axisY1
    }
    LineSeries {
        id: lineSeries5
        name: "signal 4"
        color: "black"
        axisX: axisX
        axisY: axisY1
    }
    LineSeries {
        id: lineSeries6
        name: "signal 4"
        color: "black"
        axisX: axisX
        axisY: axisY1
    }
    LineSeries {
        id: lineSeries7
        name: "signal 4"
        color: "black"
        axisX: axisX
        axisY: axisY1
    }
    LineSeries {
        id: lineSeries8
        name: "signal 4"
        color: "black"
        axisX: axisX
        axisY: axisY1
    }
    LineSeries {
        id: lineSeries9
        name: "signal 4"
        color: "black"
        axisX: axisX
        axisY: axisY1
    }
    LineSeries {
        id: lineSeries10
        name: "signal 4"
        color: "black"
        axisX: axisX
        axisY: axisY1
    }
/*
    Connections {
        target: graph_qml
        onValueChanged: {
            console.log("valueChanged")
            if(lineSeries1.count > points_number)
                lineSeries1.remove(0);
            lineSeries1.append(graph_qml.values.x, graph_qml.values.x)
            axisX.min = lineSeries1.at(0).x
            axisX.max = lineSeries1.at(lineSeries1.count-1).x
        }
    }
*/
    Timer {
        id: refreshTimer
        interval: 1 / 60 * 1000 // 60 Hz
        running: true
        repeat: true
        onTriggered: {
            graph.print_coord(chartView.series(0), 0)
            graph.print_coord(chartView.series(1), 1)
        }
    }

}
