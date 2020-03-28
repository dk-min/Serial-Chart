import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtQuick.Controls.Material 2.0
import QtCharts 2.12

ApplicationWindow {
    id: chartwindow
    width: 1600; height: 1000

    Text {
        id: element
        color: "#ffffff"
        text: qsTr("BaudRate : \t") + serialC.ReadBaudrate + qsTr("\t") + qsTr("Com Port : \t") + serialC.Comport
        anchors.rightMargin: 10
        anchors.leftMargin: 803
        anchors.bottomMargin: 7
        anchors.topMargin: 948
        anchors.fill: parent
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 12
    }

    ChartView {
        id: linechart
        x: 0
        y: 0
        width: 1600
        height: 900
        theme: ChartView.ChartThemeBrownSand
        property bool openGL: true
        property bool openGLSupported: true
        animationOptions: ChartView.NoAnimation
        onOpenGLChanged: {
            if (openGLSupported) {
                series("signal 1").useOpenGL = openGL;
                series("signal 2").useOpenGL = openGL;
            }
        }
        Component.onCompleted: {
            if (!series("signal 1").useOpenGL) {
                openGLSupported = false
                openGL = false
            }
        }
        ValueAxis {
            id: axisX1
            min: 0
            max: 256
        }

        ValueAxis {
            id: axisY1
            min: 0
            max: 1023
        }
        LineSeries {
            id: lineSeries1
            name: "signal 1"
            axisX: axisX1
            axisY: axisY1
            useOpenGL: linechart.openGL

        }
        LineSeries {
            id: lineSeries2
            name: "signal 2"
            axisX: axisX1
            axisY: axisY1
            useOpenGL: linechart.openGL

        }


    }
    Timer {
        id: refreshTimer
        interval: 1 / 1000 * 1000 // 60 Hz
        running: true
        repeat: true
        onTriggered: {
            serialC.update(linechart.series(0), 0);
            serialC.update(linechart.series(1), 1);
            //serialC.nofunc()
        }
    }

}




