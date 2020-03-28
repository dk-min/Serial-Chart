import QtQuick 2.4
import QtQuick.Controls.Material 2.0
import QtCharts 2.3

Chart2Form {
    id: chartwindow
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
        id: line
        x: 0
        y: 0
        width: 1600
        height: 942
        count: 256
        LineSeries {
            name: "LineSeries"
            XYPoint {
                x: 0
                y: 2
            }

            XYPoint {
                x: 1
                y: 1.2
            }

            XYPoint {
                x: 2
                y: 3.3
            }

            XYPoint {
                x: 5
                y: 2.1
            }
        }
    }
}
