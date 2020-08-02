import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    title: "settings"
    id: settings

    function switchTo(v){
        settingsStack.setCurrentIndex(v)
    }

    TabBar {
        id: settingsTabBar
        width: parent.width

        TabButton {
            text: qsTr("UI")
            onClicked: {switchTo(0)}
        }

        TabButton {
            text: qsTr("Media")
            onClicked: {switchTo(1)}
        }

        TabButton {
            text: qsTr("Navigation")
            onClicked: {switchTo(2)}
        }
    }

    SwipeView {
        id: settingsStack
        currentIndex: 0
        anchors.fill: parent
        anchors.top: parent.top
        anchors.topMargin: 55

        SettingsUI{}
        SettingsMedia{}
        SettingsNavigation{}
    }
}
