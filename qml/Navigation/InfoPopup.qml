import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtPositioning 5.6

import io.eberlein.carpi.map 1.0

Popup {
    id: navigationInfoPopup
    modal: true
    width: 400
    height: 240
    anchors.centerIn: parent

    property PositionSource gpsSource

    property double latitude
    property double longitude

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    signal routeButtonClicked

    LocationInfoModel {
        id: locationInfoModel

        onFoundLocationInfo: {
            lblPostal.text = postal
            lblCity.text = city
            lblStreet.text = street
            lblHouseNr.text = houseNr
            lblTitle.text = street + " " + houseNr
        }
    }

    RoutingListModel {
        id: route

        onComputingChanged: {
            var d = "could not be calculated"
            if(route.count > 0){
                var v = 0
                var s = "m"
                if(route.length > 1000) {v = route.length / 1000; s = "km"}
                v = Math.round(v * 100) / 100
                d = v + " " + s
            }
            lblDistanceValue.text = d
            lblDurationValue.text = Math.round((route.duration / 60) * 10) / 10 + " min"
        }
    }

    function show(latitude, longitude) {
        visible = true
        this.latitude = latitude
        this.longitude = longitude
        lblLatitudeValue.text = latitude
        lblLongitudeValue.text = longitude
        locationInfoModel.setLocation(latitude, longitude)

        var p = gpsSource.position.coordinate
        var f = route.locationEntryFromPosition(p.latitude, p.longitude)
        var t = route.locationEntryFromPosition(latitude, longitude)
        route.setStartAndTarget(f, t)
    }

    contentItem: Item {
        anchors.fill: parent

        Label {
            id: lblTitle
            font.pointSize: 14
            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.top: parent.top
            anchors.topMargin: 4
        }

        Label {
            id: lblLatitude
            text: "Latitude:"
            anchors.left: lblTitle.left
            anchors.top: lblTitle.bottom
            anchors.topMargin: 4
        }

        Label {
            id: lblLatitudeValue
            anchors.top: lblLatitude.top
            anchors.right: parent.right
            anchors.rightMargin: 4
        }

        Label {
            id: lblLongitude
            text: "Longitude:"
            anchors.left: lblTitle.left
            anchors.top: lblLatitude.bottom
            anchors.topMargin: 4
        }

        Label {
            id: lblLongitudeValue
            anchors.top: lblLongitude.top
            anchors.right: parent.right
            anchors.rightMargin: 4
        }

        Label {
            id: lblPostal
            anchors.left: lblTitle.left
            anchors.top: lblLongitude.bottom
            anchors.topMargin: 16
        }

        Label {
            id: lblCity
            anchors.left: lblPostal.right
            anchors.leftMargin: 4
            anchors.top: lblPostal.top
        }

        Label {
            id: lblStreet
            anchors.left: lblTitle.left
            anchors.top: lblCity.bottom
            anchors.topMargin: 4
        }

        Label {
            id: lblHouseNr
            anchors.left: lblStreet.right
            anchors.leftMargin: 4
            anchors.top: lblStreet.top
        }

        Label {
            id: lblDistance
            text: "Distance:"
            anchors.left: lblTitle.left
            anchors.top: lblStreet.bottom
            anchors.topMargin: 4
        }

        Label {
            id: lblDistanceValue
            anchors.left: lblDistance.right
            anchors.leftMargin: 4
            anchors.top: lblDistance.top
        }

        Label {
            id: lblDuration
            text: "Duration:"
            anchors.left: lblDistance.left
            anchors.top: lblDistance.bottom
            anchors.topMargin: 4
        }

        Label {
            id: lblDurationValue
            anchors.left: lblDuration.right
            anchors.leftMargin: 4
            anchors.top: lblDuration.top
        }

        Button {
            id: btnRoute
            text: "Route"
            anchors.left: lblDuration.left
            anchors.top: lblDuration.bottom
            anchors.topMargin: 8
            onClicked: routeButtonClicked()
        }
    }
}
