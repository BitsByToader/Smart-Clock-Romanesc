import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.VirtualKeyboard 2.15
import QtQuick.Controls.Material 2.15

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
        text: modelData.alarmHour + ":" + modelData.alarmMinutes

        font.pixelSize: 26

        anchors.right: alarmActivatedSwitch.left
        anchors.verticalCenter: wrapper.verticalCenter
    }

    ListView {
        anchors.bottom: wrapper.bottom
        anchors.bottomMargin: 15

        anchors.left: wrapper.left
        anchors.leftMargin: 25

        orientation: ListView.Horizontal

        width: 100
        height: 25

        model: modelData.alarmDays

        delegate: ItemDelegate {
            text: "Hi"

            font.pixelSize: 15
            font.italic: true
//            color: Material.color(Material.Grey)
            height: parent.height
            width: 30

        }
    }

    Switch {
        id: alarmActivatedSwitch

        checkable: true
        checked: modelData.alarmActivated

        Material.accent: Material.Blue

        anchors.right: wrapper.right
        anchors.verticalCenter: wrapper.verticalCenter

        onClicked: {
            console.log("Pressed switch for " + modelData.alarmName)
            modelData.alarmActivated = !modelData.alarmActivated
        }

    }

    MenuSeparator {
        width: wrapper.width - 25

        anchors.bottom: wrapper.bottom
        anchors.right: wrapper.right
        anchors.topMargin: 5
    }
}
