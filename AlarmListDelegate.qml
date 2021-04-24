import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.VirtualKeyboard 2.15
import QtQuick.Controls.Material 2.15
import tudor.SmartClock 1.0

Item {
    id: wrapper

    width: alarmsList.width
    height: 70

    Label {
        id: alarmName
        text: modelData.alarmName

        font.pixelSize: 22
        font.bold: true

        anchors.left: wrapper.left
        anchors.leftMargin: 25
        anchors.top: wrapper.top
    }

    Label {
        text: makeNumbersWithDoubleDigits(modelData.alarmHour) + ":" + makeNumbersWithDoubleDigits(modelData.alarmMinutes)

        font.pixelSize: 26

        anchors.right: alarmActivatedSwitch.left
        anchors.verticalCenter: wrapper.verticalCenter
    }

    Label {
        text: modelData.alarmDays !== "" ? modelData.alarmDays : "O singura data."

        font.pixelSize: 15
        font.italic: true
        color: Material.color(Material.Grey)

        anchors.bottom: wrapper.bottom
        anchors.bottomMargin: 15

        anchors.left: wrapper.left
        anchors.leftMargin: 25
    }

    Switch {
        id: alarmActivatedSwitch

        checkable: true
        checked: modelData.alarmActivated

        Material.accent: Material.Blue

        anchors.right: editAlarmButton.left
        anchors.verticalCenter: wrapper.verticalCenter

        onClicked: {
            modelData.alarmActivated = !modelData.alarmActivated

            SmartClock.alarms.updateAlarm(modelData.alarmUUID, modelData.alarmName, modelData.alarmHour, modelData.alarmMinutes, modelData.alarmDays, modelData.alarmActivated)
        }

    }

    Button {
        id: deleteAlarmButton

        text: "Sterge"
        Material.accent: Material.Red
        highlighted: true
        flat: true

        anchors.right: wrapper.right
        anchors.verticalCenter: wrapper.verticalCenter

        onClicked: {
            SmartClock.alarms.deleteAlarm(modelData.alarmUUID)
        }
    }

    Button {
        id: editAlarmButton

        text: "Editeaza"
        Material.accent: Material.Blue
        highlighted: true
        flat: true

        anchors.right: deleteAlarmButton.left
        anchors.verticalCenter: wrapper.verticalCenter

        onClicked: {
            alarmNameToUse = modelData.alarmName
            alarmHourToUse = modelData.alarmHour
            alarmMinutesToUse = modelData.alarmMinutes
            alarmRepeatsToUse = (modelData.alarmDays !== "")
            alarmDaysToUse = modelData.alarmDays.split(" ")
            dialogWillEdit = true
            alarmUUID = modelData.alarmUUID

            isAddAlarmDialogVisible = true
        }
    }

    MenuSeparator {
        width: wrapper.width - 25

        anchors.bottom: wrapper.bottom
        anchors.right: wrapper.right
        anchors.topMargin: 5
    }
}
