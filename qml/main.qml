import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.VirtualKeyboard 2.15
import Qt.labs.folderlistmodel 2.15

import utils 1.0

import "Wireless"
import "Media"
import "Navigation"
import "Settings"


ApplicationWindow {
    id: window
    visible: true
    width: 1024
    height: 600
    visibility: isFullscreen()
    minimumWidth: width
    maximumWidth: width
    minimumHeight: height
    maximumHeight: height
    title: "carpi"

    function isFullscreen(){
        if(isPi.isFile) return ApplicationWindow.Windowed
        else return ApplicationWindow.FullScreen
    }

    IsFile {
        id: isPi
        file: "/sys/firmware/devicetree/base/model"
    }

    SettingsSystem {
        id: settingsSystem
    }

    Material.theme: Material.Dark
    Material.accent: Material.Purple

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {drawer.open()}
        }

        Label {
            text: swipeView.currentItem.title
            anchors.centerIn: parent
        }
    }

    function switchTo(v){
        swipeView.setCurrentIndex(v)
        drawer.close()
    }

    Drawer {
        id: drawer
        width: window.width * 0.33
        height: window.height

        Column {
            id: drawerColumn
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Dashboard")
                width: parent.width
                onClicked: {switchTo(0)}
            }

            ItemDelegate {
                text: qsTr("Media")
                width: parent.width
                onClicked: {switchTo(1)}
            }

            ItemDelegate {
                text: qsTr("Navigation")
                width: parent.width
                onClicked: {switchTo(2)}
            }

            ItemDelegate {
                text: qsTr("Wireless")
                width: parent.width
                onClicked: {switchTo(3)}
            }

            ItemDelegate {
                text: qsTr("Settings")
                width: parent.width
                onClicked: {switchTo(4)}
            }
        }
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: 0
        interactive: false

        Dashboard {}
        Media {}
        Navigation {}
        Wireless {}
        Settings {}
    }

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
