import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.VirtualKeyboard 2.15
import QtQuick.Controls.Material 2.15
import tudor.SmartClock 1.0

ApplicationWindow {
    id: window

    //Set a minimum and maxium height/width to make the window nonresizable
    minimumHeight: 480
    maximumHeight: 480

    minimumWidth: 800
    maximumWidth: 800

    visible: true
    title: qsTr("Smart Clock")

    function makeNumbersWithDoubleDigits(number) {
        return ( parseInt( parseInt(number) / 10 ) === 0 ) ? ("0" + number) : number;
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: swipeIndicator.currentIndex

        MainView {}

        AlarmsView {}
    }

    PageIndicator {
        id: swipeIndicator

        count: 2
        currentIndex: swipeView.currentIndex
        interactive: true

        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Button {
        id: backButton
        icon.name: "back"
        icon.source: "icons/back.png"
        background: transparent

        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            swipeView.decrementCurrentIndex()
        }

        states: [
            State {
                when: swipeView.currentIndex == 0;
                PropertyChanges { target: backButton; opacity: 0 }
            },
            State {
                when: swipeView.currentIndex != 0;
                PropertyChanges { target: backButton; opacity: 1 }
            }
        ]

        transitions: Transition {
            NumberAnimation {
                property: "opacity"
                duration: 250
            }
        }
    }

    Button {
        id: forwardButton
        icon.name: "back"
        icon.source: "icons/forward.png"
        background: transparent

        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right

        onClicked: {
            swipeView.incrementCurrentIndex()
       }

        states: [
            State {
                when: swipeView.currentIndex +1 == swipeView.count;
                PropertyChanges { target: forwardButton; opacity: 0 }
            },
            State {
                when: swipeView.currentIndex + 1 < swipeView.count;
                PropertyChanges { target: forwardButton; opacity: 1 }
            }
        ]

        transitions: Transition {
            NumberAnimation {
                property: "opacity"
                duration: 250
            }
        }
    }

    Dialog {
        id: alarmRangDialog
        title: "Alarma"

        anchors.centerIn: parent

        AlarmRangDialog {}
    }

    //Used for the virtual keyboard.
    //Don't remove.
    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: window.height
        width: window.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: window.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
}
