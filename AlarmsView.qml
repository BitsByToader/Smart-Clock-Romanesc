import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.VirtualKeyboard 2.15
import QtQuick.Controls.Material 2.15
//Leave this commented to use the Qt Dialog
//Uncomment the line bellow to use the system wide dialog, which it is buggy in macOS
//import QtQuick.Dialogs 1.3
import tudor.SmartClock 1.0

Pane {
    id: alarmsViewPane

    property var alarmNameToUse: ""
    property var alarmHourToUse: 0
    property var alarmMinutesToUse: 0
    property var alarmRepeatsToUse: true
    property var alarmDaysToUse: []
    property var dialogWillEdit: false
    property var alarmUUID: ""

    Material.accent: Material.Blue

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

        onClicked: {
            alarmNameToUse = ""
            alarmHourToUse = 0
            alarmMinutesToUse = 0
            alarmRepeatsToUse = true
            alarmDaysToUse = []
            alarmUUID = ""
            dialogWillEdit = false

            addAlarmDialog.open()
        }
    }

    Label {
        id: alarmListPlaceholder
        text: "Add an alarm with the '+' button."
        opacity: SmartClock.alarms.list.length === 0 ? 100 : 0

        anchors.centerIn: parent

        color: Material.color(Material.Grey)
        font.bold: true
        font.pixelSize: 20

        Behavior on opacity {
            NumberAnimation {
                duration: 150
            }
        }
    }

    ListView {
        id: alarmsList

        width: parent.width
        height: parent.height

        anchors.top: alarmsViewTitle.bottom
        anchors.topMargin: 10
        anchors.left: parent.left

        model: SmartClock.alarms.list

        delegate: AlarmListDelegate {}

        add: Transition {
            NumberAnimation { properties: "x,y"; from: 100; duration: 1000 }
        }
    }

    Dialog {
        id: addAlarmDialog
        title: "Add an alarm"

        anchors.centerIn: parent

        AddAlarmDialogContent {}
    }
}
