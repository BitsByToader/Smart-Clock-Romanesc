import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.VirtualKeyboard 2.15
import QtQuick.Controls.Material 2.15
import tudor.SmartClock 1.0

Rectangle {
    color: "transparent"

    implicitHeight: 140
    implicitWidth: 400

    property var snoozeTime: SmartClock.settings.snoozeTime
    property var alarmRingtone: SmartClock.settings.alarmRingtone

    Label {
        id: snoozeTimeLabel

        text: "Snooze time: "
        font.italic: true
        font.pixelSize: 15

        anchors.left: parent.left
        anchors.verticalCenter: snoozeTimeField.verticalCenter
    }

    TextField {
        id: snoozeTimeField
        width: 200

        placeholderText: "Snooze minutes"
        autoScroll: true
        Material.accent: Material.Blue
        inputMask: "000" // Only allow three numbers from 0 to 9 for the snooze time.

        text: snoozeTime

        anchors.left: snoozeTimeLabel.right
        anchors.leftMargin: 10
    }

    Label {
        id: alarmSoundLabel

        text: "Alarm sound: "
        font.italic: true
        font.pixelSize: 15

        anchors.left: parent.left
        anchors.verticalCenter: alarmSoundField.verticalCenter
    }

    TextField {
        id: alarmSoundField
        width: 200

        placeholderText: "Alarm ringtone"
        autoScroll: true
        Material.accent: Material.Blue

        text: alarmRingtone

        anchors.left: alarmSoundLabel.right
        anchors.leftMargin: 10
        anchors.top: snoozeTimeField.bottom
        anchors.topMargin: 10
    }

    Button {
        id: saveSettingsButton
        text: "Save"

        Material.accent: Material.color(Material.Blue)
        highlighted: true
        flat: true

        anchors.right: parent.right
        anchors.bottom: parent.bottom

        onClicked: {
            SmartClock.settings.snoozeTime = snoozeTimeField.text
            SmartClock.settings.alarmRingtone = alarmSoundField.text

            settingsDialog.close()
        }
    }

    Button {
        id: closeSettingsDialogButton
        text: "Close"

        Material.accent: Material.color(Material.Red)
        highlighted: true
        flat: true

        anchors.right: saveSettingsButton.left
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom

        onClicked: settingsDialog.close()
    }
}
