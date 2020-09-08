import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtPositioning 5.6

import settings 1.0
import io.eberlein.carpi.map 1.0

// todo show next turn when routing
// todo stop routing when at destination6
// todo show speed cameras

Page {
    id: navigation
    title: qsTr("Navigation")

    property double destinationLatitude
    property double destinationLongitude

    function reroute(){
        var p = gpsSource.position.coordinate
        var s = routingModel.locationEntryFromPosition(p.latitude, p.longitude)
        // todo get target destination
    }

    function routeTo(lat, lon){
        var p = gpsSource.position.coordinate
        var f = routingModel.locationEntryFromPosition(p.latitude, p.longitude)
        var t = routingModel.locationEntryFromPosition(lat, lon)
        routingModel.setStartAndTarget(f, t)
    }

    NavigationSettings {
        id: settings
    }

    PositionSource {
        id: gpsSource
        updateInterval: 420 // set via settings
        active: true

        onPositionChanged: {
            var p = position
            var c = p.coordinate
            map.locationChanged(true, c.latitude, c.longitude, p.horizontalAccuracyValid, p.horizontalAccuracy)
            navigationModel.locationChanged(true, c.latitude, c.longitude, p.horizontalAccuracyValid, p.horizontalAccuracy)
        }
    }

    RoutingListModel {
        id: routingModel

        onReadyChanged: {
            var r = routingModel.routeWay
            if(r === null) return
            map.addOverlayObject(0, r)
        }

        onComputingChanged: {
            if(routingModel.count > 0){
                map.addOverlayObject(0, routingModel.routeWay)
            }
        }
    }

    NavigationModel {
        id: navigationModel
        route: routingModel.route

        onRerouteRequest: {
            if(routingModel.ready) reroute()
        }
    }

    LocationInfoModel {
        id: locationInfoModel
    }

    InfoPopup {
        id: navigationInfoPopup
        gpsSource: gpsSource

        visible: false

        onRouteButtonClicked: {
            destinationLatitude = latitude
            destinationLongitude = longitude
            routeTo(latitude, longitude)
        }
    }

    GridLayout {
        id: content
        anchors.fill: parent

        Map {
            id: map
            Layout.fillWidth: true
            Layout.fillHeight: true
            focus: true
            renderingType: "tiled"
            showCurrentPosition: true
            vehiclePosition: navigationModel.vehiclePosition

            Component.onCompleted: {
                var c = gpsSource.position.coordinate
                map.showCoordinates(c.latitude, c.longitude)
            }

            // void osmscout::MapWidget::longTap(const int screenX, const int screenY, const double lat, const double lon)
            onLongTap: navigationInfoPopup.show(lat, lon)


            ColumnLayout {
                id: dialogBtnColumn
                spacing: 20

                // anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter

                CircleButton {
                    id: btnHistory
                    label: "\u2605"
                    onClicked: {} // todo open history dialog
                }

                CircleButton {
                    id: btnFavourites
                    label: "\u2764"
                    onClicked: {} // todo
                }

                CircleButton {
                    id: btnSearch
                    label: "\u26B2"
                    textRotation: -30
                    onClicked: navigationSearchPopup.visible = true
                }

                CircleButton {
                    id: btnCenter
                    label: "\u2609"
                    onClicked: {
                        var c = gpsSource.position.coordinate
                        map.showCoordinates(c.latitude, c.longitude)
                    }
                }
            }
        }
    }

    SearchPopup {
        id: navigationSearchPopup
        visible: false
        onShowButtonClicked: map.showCoordinates(selectedLatitude, selectedLongitude)
        onRouteButtonClicked: routeTo(selectedLatitude, selectedLongitude)
    }
}
