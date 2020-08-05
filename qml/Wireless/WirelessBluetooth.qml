import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtBluetooth 5.15

Page {
    id: wirelessBluetooth
    title: "Wireless :: Bluetooth"

    function showControls(){
        return lblErrorValue.text != "none"
    }

    Label {
        id: lblError
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 4
        anchors.leftMargin: 4
        text: "Error:"
    }

    Label {
        id: lblErrorValue
        anchors.top: lblError.top
        anchors.left: lblError.right
        anchors.leftMargin: 4
    }

    ComboBox {
        id: discovery
        visible: showControls()
        anchors.top: lblError.bottom
        anchors.topMargin: 4
        anchors.left: lblError.left
        textRole: "text"
        valueRole: "value"
        model: [
            {value: BluetoothDiscoveryModel.FullServiceDiscovery, text: qsTr("Full")},
            {value: BluetoothDiscoveryModel.MinimalServiceDiscovery, text: qsTr("Service")},
            {value: BluetoothDiscoveryModel.DeviceDiscovery, text: qsTr("Device")}
        ]
    }

    Button {
        id: btnScan
        visible: showControls()
        anchors.top: discovery.top
        anchors.left: discovery.right
        anchors.leftMargin: 16
        text: "Scan"
        onClicked: {
            // todo populate foundDevices list
        }
    }

    ListView {
        id: foundDevicesView
        visible: showControls()
        anchors.top: discovery.bottom
        anchors.topMargin: 8
        anchors.left: discovery.left
        anchors.bottom: parent.bottom
        width: 200
        model: bluetoothModel
        delegate: deviceItemDelegate

        Component {
            id: deviceItemDelegate

            Item {
                height: lblMac.implicitHeight + lblName.implicitHeight + 8
                width: foundDevicesView.width

                Label {
                    id: lblMac
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.leftMargin: 4
                    anchors.topMargin: 4
                    text: remoteAddress
                }

                Label {
                    id: lblName
                    anchors.left: lblMac.left
                    anchors.top: lblMac.bottom
                    anchors.topMargin: 4
                    text: deviceName
                }
            }
        }
    }

    ListView {
        id: foundServicesView
        visible: showControls()
        anchors.left: foundDevicesView.right
        anchors.leftMargin: 8
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        // todo model, on select show options what to do with service
    }

    BluetoothDiscoveryModel {
        id: bluetoothModel
        discoveryMode: discovery.currentValue

        function displayError(){
            var v = "none"
            if(error == BluetoothDiscoveryModel.InputOutputError) v = "IO Failure during device discovery"
            else if(error == BluetoothDiscoveryModel.PoweredOffError) v = "Bluetooth device is off"
            else if(error == BluetoothDiscoveryModel.InvalidBluetoothAdapterError) v = "No default Bluetooth device availiable"
            else if(error == BluetoothDiscoveryModel.UnknownError) v = "Unknown"
            lblErrorValue.text = v
        }

        onDeviceDiscovered: {
            displayError()
            console.log("found device: ", device.deviceName, ", with address: ", device.remoteAddress)
            // todo
        }

        onServiceDiscovered: {
            // todo
        }

        Component.onCompleted: {
            displayError()
        }
    }

}
