import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    title: "Settings :: Media"
    id: settingsMedia

    function switchTo(v){
        mediaStack.setCurrentIndex(v)
    }

    TabBar {
        id: mediaTabBar
        width: parent.width

        TabButton {
            text: qsTr("Music")
            onClicked: {switchTo(0)}
        }

        TabButton {
            text: qsTr("Video")
            onClicked: {switchTo(1)}
        }
    }

    SwipeView {
        id: mediaStack
        anchors.fill: parent
        anchors.top: parent.top
        anchors.topMargin: 55
        interactive: false
        currentIndex: 0

        SettingsMusic {}
        SettingsVideo {}
    }
}
