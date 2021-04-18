import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.VirtualKeyboard 2.15
import QtQuick.Controls.Material 2.15
import tudor.SmartClock 1.0

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

        text: alarmNameToUse

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

        currentIndex: alarmHourToUse

        flat: true
        model: 24
        validator: IntValidator {
            bottom: 1;
            top: 23;
        }

        displayText: parseInt(parseInt(currentText) / 10) === 0 ? "0" + currentText : currentText
        Material.accent: Material.Blue

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

        currentIndex: alarmMinutesToUse

        flat: true
        model: 60
        validator: IntValidator {
            bottom: 1;
            top: 59;
        }

        displayText: parseInt(parseInt(currentText) / 10) === 0 ? "0" + currentText : currentText
        Material.accent: Material.Blue

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
        checked: alarmRepeatsToUse
        Material.accent: Material.Blue

        anchors.left: alarmRepeatsLabel.right
        anchors.top: alarmHourPicker.bottom
    }

    Label {
        id: alarmDaysLabel

        visible: alarmRepeatsSwitch.checked

        text: "Days"
        font.italic: true
        font.pixelSize: 15

        anchors.left: parent.left
        anchors.verticalCenter: alarmDaysButtons.verticalCenter

        states: [
            State {
                when: !alarmRepeatsSwitch.checked;
                PropertyChanges { target: alarmDaysLabel; opacity: 0 }
                PropertyChanges { target: alarmDaysButtons; opacity: 0 }
            },
            State {
                when: alarmRepeatsSwitch.checked;
                PropertyChanges { target: alarmDaysLabel; opacity: 1 }
                PropertyChanges { target: alarmDaysButtons; opacity: 1 }
            }
        ]

        transitions: Transition {
            NumberAnimation {
                property: "opacity"
                duration: 250
            }
        }
    }

    ListView {
        id: alarmDaysButtons

        visible: alarmRepeatsSwitch.checked

        width: 525
        height: 50

        model: ["Lu", "Ma", "Mi", "Jo", "Vi", "Sa", "Du"]
        orientation: ListView.Horizontal

        delegate: CheckDelegate {
            id: dayOfTheWeekCheckbox
            text: modelData

            checked: alarmDaysToUse.includes(modelData)
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
            var alarmDaysString = ""

            if ( alarmRepeatsSwitch.checked ) {
                for ( var i = 0; i < alarmDaysButtons.children[0].children.length - 1; i++ ) {
                    if ( alarmDaysButtons.children[0].children[i].checked ) {
                        alarmDaysString += alarmDaysButtons.children[0].children[i].text

                        if ( i !== alarmDaysButtons.children[0].children.length - 2 ) {
                            alarmDaysString += " "
                        }
                    }
                }
                alarmDaysString.substring(0, alarmDaysString.length - 1);
            }

            if ( dialogWillEdit ) {
                SmartClock.alarms.updateAlarm(alarmUUID, alarmNameField.text, alarmHourPicker.currentIndex, alarmMinutesPicker.currentIndex, alarmDaysString, true)
                console.log("Alarm updated");
            } else {
                SmartClock.alarms.addAlarm(alarmNameField.text, alarmHourPicker.currentIndex, alarmMinutesPicker.currentIndex, alarmDaysString, true)
                console.log("New alarm added.")
            }
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
