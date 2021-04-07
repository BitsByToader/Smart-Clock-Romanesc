import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.VirtualKeyboard 2.15
import QtQuick.Controls.Material 2.15

ApplicationWindow {
    id: window
    width: 800
    height: 480
    visible: true
    title: qsTr("SmartClock")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: swipeIndicator.currentIndex

        Pane {
            Text {
                id: wow
                text: qsTr("sup bitch")

                color: "#ffffff"
                font.bold: true
            }
        }

        Pane {
            Text {
                id: wowagain
                text: qsTr("who's that biitch?")

                color: "#ffffff";
                font.bold: true
            }
        }
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
//        opacity: modulesList.currentIndex == 0 ? 0 : 1
        icon.name: "back"
        icon.source: "icons/back.png"
        background: transparent //dirty trick to bug out QML and to remove the background

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
        background: transparent //dirty trick to bug out QML and to remove the background

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
