import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.VirtualKeyboard 2.15
import QtQuick.Controls.Material 2.15

Pane {
    id: mainViewPane

    Label {
        id: inspirationalQuote
        text: "To be or not to be, that is the question."

        font.italic: true
        font.weight: Font.Light
        font.pixelSize: 17
        color: Material.color(Material.Grey)

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 40
    }

    Label {
        id: clockTime
        text: "23:59"

        font.bold: true
        font.weight: Font.Black
        font.pixelSize: 100
        font.letterSpacing: 10

        anchors.centerIn: parent
        anchors.verticalCenterOffset: -35
    }

    Label {
        id: clockDate
        text: "Sunday,  4 April 2069"

        font.italic: true
        font.weight: Font.Light
        font.pixelSize: 25

        anchors.centerIn: parent
        anchors.verticalCenterOffset: 35
    }

    Label {
        id: alarmStatus
        text: "You have an alarm for tomorrow morning at 7 o'clock."

        font.italic: true
        font.weight: Font.Light
        font.pixelSize: 17
        color: Material.color(Material.Grey)

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: cancelNextAlarmButton.bottom
        anchors.bottomMargin: 45
    }

    Button {
        id: cancelNextAlarmButton

        text: "Cancel"
        highlighted: true
        flat: true
        Material.accent: Material.Blue

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
