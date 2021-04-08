import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.VirtualKeyboard 2.15
import QtQuick.Controls.Material 2.15

Pane {
    id: alarmsViewPane

    ListModel {
        id: alarmsModel

        ListElement {
            name: "Alarma"
            time: "7am"
            activated: false
        }
        ListElement {
            name: "Te drecu'"
            time: "3am"
            activated: true
        }
        ListElement {
            name: "Scoala vietii"
            time: "never fraere"
            activated: true
        }
    }

    Label {
        id: alarmsViewTitle

        text: "Alarms"
        font.pointSize: 30
        font.bold: true

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 10
    }

    RoundButton {
        id: addAlarmButton

        text: "+"

        width: 48
        height: 48
        radius: 24

        font.pixelSize: 18
        font.bold: true
        flat: false

        Material.foreground: "#90CAF9"

        anchors.top: parent.top
        anchors.right: parent.right
        anchors.rightMargin: 10
    }

    ListView {
        id: alarmsList

        width: parent.width
        height: parent.height

        anchors.top: alarmsViewTitle.bottom
        anchors.topMargin: 10
        anchors.left: parent.left

        model: alarmsModel

        delegate: Item {
            id: wrapper

            width: alarmsList.width
            height: 55

            Label {
                id: alarmName
                text: name

                anchors.left: wrapper.left
                anchors.top: wrapper.top
                anchors.leftMargin: 25
            }

            Label {
                text: time

                anchors.left: wrapper.left
                anchors.top: alarmName.bottom

                anchors.topMargin: 10
                anchors.leftMargin: 25
            }

            Switch {
                checkable: true
                checked: activated

                Material.accent: Material.Blue

                anchors.right: wrapper.right
                anchors.verticalCenter: wrapper.verticalCenter

            }

            MenuSeparator {
                width: wrapper.width - 25

                anchors.bottom: wrapper.bottom
                anchors.right: wrapper.right
                anchors.topMargin: 5
            }
        }
    }
}
