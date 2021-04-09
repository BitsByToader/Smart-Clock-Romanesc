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
        text: name

        font.pixelSize: 22
        font.bold: true

        anchors.left: wrapper.left
        anchors.leftMargin: 25
        anchors.top: wrapper.top
    }

    Label {
        text: time

        font.pixelSize: 26

        anchors.right: alarmActivatedSwitch.left
        anchors.verticalCenter: wrapper.verticalCenter
    }

    Label {
        text: days

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