import QtQuick 2.0
import QtCharts 2.0
import com.serial 1.0
import com.graph 1.0

ChartView {
    id: chartView

    antialiasing: true
    theme: ChartView.ChartThemeQt
    //backgroundColor: "#525357"
    //backgroundColor: "#00ff00"
    backgroundRoundness: 0

    Graph_qml{
        id: graph_qml
    }

    ValueAxis {
        id: axisY
        min: 0
        max: 80
    }

    ValueAxis {
        id: axisX
        min: 0
        max: 1000
        gridVisible: false
    }
/*
    ScatterSeries {
        id: scatter1
        markerShape: "MarkerShapeCircle"
        markerSize: 4
        borderWidth: 0
        name: "signal 8"
        color: "blue"
        axisX: axisX
        axisY: axisY
    }*/

    LineSeries {
        id: lineSeries1
        name: "signal 1"
        color: "red"
        axisX: axisX
        axisY: axisY
    }

    LineSeries {
        id: lineSeries2
        name: "signal 2"
        color: "green"
        axisX: axisX
        axisY: axisY
    }
    LineSeries {
        id: lineSeries3
        name: "signal 3"
        color: "blue"
        axisX: axisX
        axisY: axisY
    }
    LineSeries {
        id: lineSeries4
        name: "signal 4"
        color: "black"
        axisX: axisX
        axisY: axisY
    }
    LineSeries {
        id: lineSeries5
        name: "signal 5"
        color: "black"
        axisX: axisX
        axisY: axisY
    }
    LineSeries {
        id: lineSeries6
        name: "signal 6"
        color: "black"
        axisX: axisX
        axisY: axisY
    }
    LineSeries {
        id: lineSeries7
        name: "signal 7"
        color: "black"
        axisX: axisX
        axisY: axisY
    }
    LineSeries {
        id: lineSeries8
        name: "signal 8"
        color: "black"
        axisX: axisX
        axisY: axisY
    }
    LineSeries {
        id: lineSeries9
        name: "signal 9"
        color: "black"
        axisX: axisX
        axisY: axisY
    }
    LineSeries {
        id: lineSeries10
        name: "signal 10"
        color: "black"
        axisX: axisX
        axisY: axisY
    }

    Timer {

        interval: 1 / 60 * 1000
        running: true
        repeat: true
        onTriggered: {
            graph.print_coord(chartView.series(0), 0)
            graph.print_coord(chartView.series(1), 1)
            graph.print_coord(chartView.series(2), 2)
            graph.print_coord(chartView.series(3), 3)
            graph.print_coord(chartView.series(4), 4)
            graph.print_coord(chartView.series(5), 5)
            graph.print_coord(chartView.series(6), 6)
            graph.print_coord(chartView.series(7), 7)
            graph.print_coord(chartView.series(8), 8)
            graph.print_coord(chartView.series(9), 9)

            //axisX.min = lineSeries1.at(0).x
            //axisX.max = lineSeries1.at(lineSeries1.count -1).x
            graph.get_Y_axis(chartView.axisX(series(0)), 0, 0)
        }
    }

    Timer{
        id: resizeTimer
        interval: 500
        running: true
        repeat: true
        onTriggered: {
            graph.set_axis()
            graph.get_Y_axis(chartView.axisY(series(0)), 0, 1)
        }
    }

}
