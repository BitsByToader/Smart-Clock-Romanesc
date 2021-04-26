import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.VirtualKeyboard 2.15
import QtQuick.Controls.Material 2.15
import tudor.SmartClock 1.0

Pane {
    id: mainViewPane

    Label {
        id: inspirationalQuote
        text: SmartClock.quotes.quote

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
        text: SmartClock.hour + ":" + SmartClock.minute

        font.bold: true
        font.weight: Font.Black
        font.pixelSize: 100
        font.letterSpacing: 10

        anchors.centerIn: parent
        anchors.verticalCenterOffset: -35
    }

    Label {
        id: clockDate
        text: SmartClock.date

        font.italic: true
        font.weight: Font.Light
        font.pixelSize: 25

        anchors.centerIn: parent
        anchors.verticalCenterOffset: 35
    }

    Label {
        id: alarmStatus
        text: SmartClock.headline

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

        visible: alarmStatus.text == "Nu aveti nici o alarma." ? false : true

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter

        onClicked: SmartClock.alarms.cancelNextAlarm()
    }
}
