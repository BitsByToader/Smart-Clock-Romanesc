import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.VirtualKeyboard 2.15
import QtQuick.Controls.Material 2.15

Pane {
    id: alarmsViewPane

    ListModel {
        id: alarmsModel

        ListElement {
            name: "Copilu'"
            time: "06:30"
            days: "Lu Ma Mi Jo Vi Sa Du"
            activated: false
        }
        ListElement {
            name: "Pastile"
            time: "14:45"
            days: "Lu Ma Mi Jo Vi Sa Du"
            activated: true
        }
        ListElement {
            name: "Munca"
            time: "09:00"
            days: "Lu Ma Mi Jo Vi"
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

        delegate: AlarmListDelegate {}
    }
}
