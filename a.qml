import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtQuick.Controls.Material 2.0
import QtCharts 2.12

Item {
    ApplicationWindow {
        objectName: applicationWindow
        visible: true
        width: 320
        height: 240
        title: qsTr("Human & System Lab.")

        Material.theme: Material.Grey

        Grid {
            id: grid
            antialiasing: false
            transformOrigin: Item.Center
            flow: Grid.LeftToRight
            spacing: 10
            rows: 3
            columns: 2
            anchors.rightMargin: 20
            anchors.leftMargin: 30
            anchors.bottomMargin: 20
            anchors.topMargin: 40
            anchors.fill: parent

            Text {
                id: serial
                width: 140
                height: 40
                color: "#ffffff"
                text: qsTr("Serial Port")
                verticalAlignment: Text.AlignVCenter
                font.bold: true
                font.pixelSize: 20
            }

            ComboBox {
                id: comboBox
                font.bold: true
                font.pixelSize: 20
                model: portnum.comboList
            }

            Text {
                id: serial1
                width: 140
                height: 40
                color: "#ffffff"
                text: qsTr("Baud Rate")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.bold: true
                font.pixelSize: 20
            }

            ComboBox {
                id: comboBox1
                model: ["9600", "115200"]
                font.bold: true
                font.pixelSize: 20
            }

            Button {
                id: button
                text: qsTr("Connect!")
                onClicked: {
                    serialC.ReadBaudrate = comboBox1.currentText
                    serialC.Comport = comboBox.currentText
                    serialC.initserial()
                }
            }

            Button {
                id: button1
                text: qsTr("Quit")
                onClicked: {
                    Qt.quit()
                }
            }
        }

    }

    ApplicationWindow {
        objectName: chartwindow
        width: 1600; height: 1000
        Material.theme: Material.Grey

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

            Timer {
                id: refreshTimer
                interval: 1 / 60 * 1000 // 60 Hz
                running: true
                repeat: true
                onTriggered: {
                    serialC.update(linechart.series(0), 0);
                    serialC.update(linechart.series(1), 1);
                    //serialC.nofunc()
                }
            }
        }

    }
}
