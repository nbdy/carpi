import QtQuick 2.15
import QtQuick.Controls 2.15
import QtPositioning 5.15

Page {
    id: dashboard
    width: 1024
    height: 550
    title: qsTr("Dashboard")

    PositionSource {
        id: gpsSource
        updateInterval: 420 // set via settings
        active: true
        preferredPositioningMethods: PositionSource.SatellitePositioningMethods // set via settings

        onPositionChanged: {
            var coord = gpsSource.position.coordinate
            lbl_gps_fixed_value.text = "true"
            lbl_gps_latitude_value.text = coord.latitude
            lbl_gps_longitude_value.text = coord.longitude
            speedGauge.value = gpsSource.position.speed
        }
    }

    Label {
        id: lbl_gps_fixed
        anchors.bottom: lbl_gps_latitude.top
        anchors.left: lbl_gps_latitude.left
        text: "is fixed:"
    }

    Label {
        id: lbl_gps_fixed_value
        anchors.left: lbl_gps_latitude_value.left
        anchors.bottom: lbl_gps_fixed.bottom
        text: "false"
    }

    Label {
        id: lbl_gps_latitude
        anchors.bottom: lbl_gps_longitude.top
        anchors.left: lbl_gps_longitude.left
        text: "Latitude:"
    }

    Label {
        id: lbl_gps_latitude_value
        anchors.top: lbl_gps_latitude.top
        anchors.left: lbl_gps_longitude_value.left
        text: "42.121212"
    }

    Label {
        id: lbl_gps_longitude
        anchors.top: speedGauge.bottom
        anchors.left: speedGauge.horizontalCenter
        anchors.leftMargin: -lbl_gps_longitude.contentWidth
        text: "Longitude:"
    }

    Label {
        id: lbl_gps_longitude_value
        anchors.top: lbl_gps_longitude.top
        anchors.left: speedGauge.horizontalCenter
        anchors.leftMargin: 4
        text: "12.334455"
    }

    SpeedGauge { // todo digital speed value
        id: speedGauge
        anchors.right: parent.right
        anchors.rightMargin: 16
        anchors.top: parent.top
        anchors.topMargin: 16
    }
}
