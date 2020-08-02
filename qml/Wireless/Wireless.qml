import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: wireless
    title: "Wireless"

    function switchTo(v){
        wirelessStack.setCurrentIndex(v)
    }

    TabBar {
        id: wirelessTabBar
        anchors.fill: parent

        TabButton {
            text: qsTr("WiFi")
            onClicked: {switchTo(0)}
        }

        TabButton {
            text: qsTr("Bluetooth")
            onClicked: {switchTo(1)}
        }
    }

    SwipeView {
        id: wirelessStack
        anchors.top: parent.top
        anchors.topMargin: 55
        anchors.fill: parent
        currentIndex: 0
        interactive: false

        WirelessWiFi{}
        WirelessBluetooth{}
    }
}
