import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import tudor.SmartClock 1.0

Rectangle {
    implicitHeight: 50
    implicitWidth: 300

    color: "transparent"

    Connections {
        target: SmartClock.alarms

        function onRingAlarmUI() {
            alarmRangDialog.open()
        }
    }

    Text {
        text: 'Alarma "' + SmartClock.alarms.nextAlarm.alarmName + '" a sunat la ora ' + makeNumbersWithDoubleDigits(SmartClock.alarms.nextAlarm.alarmHour) + ":" + makeNumbersWithDoubleDigits(SmartClock.alarms.nextAlarm.alarmMinutes) + "."
        color: "white"
        font.italic: true

        anchors.bottom: closeAlarmDialogButton.top
    }

    Button {
        id: closeAlarmDialogButton
        text: "Inchide"

        Material.accent: Material.color(Material.Blue)
        highlighted: true
        flat: true

        anchors.right: parent.right
        anchors.bottom: parent.bottom

        onClicked: {
            SmartClock.alarms.constructNewHeadline()
            alarmRangDialog.close()
        }
    }

    Button {
        id: snoozeAlarmButton
        text: "Amana"

        Material.accent: Material.color(Material.Red)
        highlighted: true
        flat: true

        anchors.right: closeAlarmDialogButton.left
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom

        onClicked: {
            SmartClock.alarms.snoozeAlarm()
            alarmRangDialog.close()
        }
    }
}
