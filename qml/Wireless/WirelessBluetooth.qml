import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtBluetooth 5.15

Page {
    id: wirelessWiFi
    title: "Wireless :: Bluetooth"

    ComboBox {
        id: discovery
        anchors.top: parent.top
        anchors.topMargin: 4
        anchors.left: parent.left
        anchors.leftMargin: 4
        textRole: "text"
        valueRole: "value"
        model: [
            {value: BluetoothDiscoveryModel.FullServiceDiscovery, text: qsTr("Full")},
            {value: BluetoothDiscoveryModel.MinimalServiceDiscovery, text: qsTr("Service")},
            {value: BluetoothDiscoveryModel.DeviceDiscovery, text: qsTr("Device")}
        ]
    }

    BluetoothDiscoveryModel {
        id: bluetoothModel
        discoveryMode: discovery.currentValue

        onDeviceDiscovered: {
            console.log("found device: ", device.deviceName, ", with address: ", device.remoteAddress)
            // todo
        }

        onServiceDiscovered: {
            // todo
        }
    }

}
