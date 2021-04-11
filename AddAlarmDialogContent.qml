import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.VirtualKeyboard 2.15
import QtQuick.Controls.Material 2.15

Rectangle {
    color: "transparent"

    implicitHeight: 250
    implicitWidth: 620

    Label {
        id: alarmNameLabel

        text: "Alarm name: "
        font.italic: true
        font.pixelSize: 15

        anchors.left: parent.left
        anchors.verticalCenter: alarmNameField.verticalCenter
    }

    TextField {
        id: alarmNameField

        placeholderText: "Alarm name"
        autoScroll: true
        Material.accent: Material.Blue

        anchors.left: alarmNameLabel.right
        anchors.leftMargin: 10
    }

    Label {
        id: timePickerLabel

        text: "Time: "
        font.italic: true
        font.pixelSize: 15

        anchors.left: parent.left
        anchors.verticalCenter: alarmHourPicker.verticalCenter
    }

    ComboBox {
        id: alarmHourPicker

        flat: true
        model: 25
        validator: IntValidator {
            bottom: 1;
            top: 24;
        }
        displayText: parseInt(parseInt(currentText) / 10) === 0 ? "0" + currentText : currentText

        width: 70

        anchors.top: alarmNameField.bottom
        anchors.left: timePickerLabel.right
    }

    Label {
        id: separator

        text: ":"
        font.bold: true
        font.pixelSize: 20

        anchors.left: alarmHourPicker.right
        anchors.leftMargin: 5
        anchors.top: alarmNameField.bottom
        anchors.topMargin: 10
    }

    ComboBox {
        id: alarmMinutesPicker

        flat: true
        model: 61
        validator: IntValidator {
            bottom: 1;
            top: 60;
        }
        displayText: parseInt(parseInt(currentText) / 10) === 0 ? "0" + currentText : currentText

        width: 70

        anchors.top: alarmNameField.bottom
        anchors.left: separator.right
        anchors.leftMargin: 5
    }

    Label {
        id: alarmRepeatsLabel

        text: "Repeats"
        font.italic: true
        font.pixelSize: 15

        anchors.left: parent.left
        anchors.verticalCenter: alarmRepeatsSwitch.verticalCenter
    }

    Switch {
        id: alarmRepeatsSwitch

        checkable: true
        checked: true
        Material.accent: Material.Blue

        anchors.left: alarmRepeatsLabel.right
        anchors.top: alarmHourPicker.bottom
    }

    Label {
        id: alarmDaysLabel

        text: "Days"
        font.italic: true
        font.pixelSize: 15

        anchors.left: parent.left
        anchors.verticalCenter: alarmDaysButtons.verticalCenter
    }

    ListView {
        id: alarmDaysButtons

        width: 525
        height: 50

        model: ["Lu", "Ma", "Mi", "Jo", "Vi", "Sa", "Du"]
        orientation: ListView.Horizontal

        delegate: CheckDelegate {
            id: dayOfTheWeekCheckbox
            text: modelData

            checked: true
            Material.accent: Material.Blue
        }

        anchors.left: alarmDaysLabel.right
        anchors.leftMargin: 5
        anchors.top: alarmRepeatsSwitch.bottom
    }

    Button {
        id: addAlarmSaveButton
        text: "Save"

        Material.accent: Material.color(Material.Blue)
        highlighted: true
        flat: true

        anchors.right: parent.right
        anchors.bottom: parent.bottom

        onClicked: {
            console.log("New alarm added.")
            addAlarmDialog.close()
        }
    }

    Button {
        text: "Cancel"

        Material.accent: Material.color(Material.Red)
        highlighted: true
        flat: true

        anchors.right: addAlarmSaveButton.left
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom

        onClicked: {
            console.log("New alarm discarded")
            addAlarmDialog.close()
        }
    }
}
