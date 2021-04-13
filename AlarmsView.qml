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
    property var isAddAlarmDialogVisible: false

    Material.accent: Material.Blue

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

        onClicked: {
            isAddAlarmDialogVisible = true

            /*var indexToDelete = 1;
            var myArray = []

            for ( var i = 0; i < 3; i++ ) {
                if ( SmartClock.alarms[i].alarmName !== SmartClock.alarms[indexToDelete].alarmName ) {
                    myArray.push(SmartClock.alarms[i])
                }
            }

            SmartClock.alarms = myArray*/

            //This is how to delete something from the array^^^
            //Because I only expose to QML a QList, the Js Engine doesn't know how to push, pop, splice etc on it
            //Thus, I can't use any nice functions so I have to do some gymnastics like this by only reading from it and completely rewriting the list.
            //However this can be easily bypassed by not manipulating the list from QML, only from C++, which is honestly more sane anyways.

            SmartClock.test();
        }
    }

    ListView {
        id: alarmsList

        width: parent.width
        height: parent.height

        anchors.top: alarmsViewTitle.bottom
        anchors.topMargin: 10
        anchors.left: parent.left

        model: SmartClock.alarms

        delegate: AlarmListDelegate {}
    }

    Dialog {
        id: addAlarmDialog
        visible: isAddAlarmDialogVisible
        title: "Add an alarm"

        anchors.centerIn: parent

        onAccepted: {
            console.log("Alarm added!")
        }

        onRejected: {
            console.log("New alarm discarded")
        }

        AddAlarmDialogContent {}
    }
}
