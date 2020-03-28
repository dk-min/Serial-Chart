import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 320
    height: 420
    title: qsTr("Human & System Lab.")

    Material.theme: Material.Grey

    Grid {
        id: grid
        antialiasing: false
        transformOrigin: Item.Center
        flow: Grid.LeftToRight
        spacing: 10
        rows: 7
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

        Text {
            id: xhigh
            width: 140
            height: 40
            color: "#ffffff"
            text: qsTr("set Xhigh")
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 20
            font.bold: true
            horizontalAlignment: Text.AlignLeft
        }


        TextArea {
            id: textArea1
            text: qsTr("2048")
            font.pixelSize: 20
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: ylow
            width: 140
            height: 40
            color: "#ffffff"
            text: qsTr("set Ylow")
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 20
            font.bold: true
            horizontalAlignment: Text.AlignLeft
        }


        TextArea {
            id: textArea2
            text: qsTr("0")
            font.pixelSize: 20
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: yhigh
            width: 140
            height: 40
            color: "#ffffff"
            text: qsTr("set Yhigh")
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 20
            font.bold: true
            horizontalAlignment: Text.AlignLeft
        }

        TextArea {
            id: textArea3
            text: qsTr("1024")
            font.pixelSize: 20
            verticalAlignment: Text.AlignVCenter
        }

        Button {
            id: button
            text: qsTr("Connect!")
            onClicked: {
                serialC.ReadBaudrate = comboBox1.currentText
                serialC.Comport = comboBox.currentText
                windowC.setXhigh(textArea1.text);
                windowC.setYlow(textArea2.text);
                windowC.setYhigh(textArea3.text);
                windowC.start();
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
























