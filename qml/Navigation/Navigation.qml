import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtPositioning 5.6

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
            var p = gpsSource.position.coordinate
            var f = routingModel.locationEntryFromPosition(p.latitude, p.longitude)
            var t = routingModel.locationEntryFromPosition(latitude, longitude)
            routingModel.setStartAndTarget(f, t)
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
            renderingType: "tiled" // plane
            showCurrentPosition: true
            vehiclePosition: navigationModel.vehiclePosition

            property var overlayWay: map.createOverlayWay("_route")

            Component.onCompleted: {
                var c = gpsSource.position.coordinate
                map.showCoordinates(c.latitude, c.longitude)
            }

            // void osmscout::MapWidget::longTap(const int screenX, const int screenY, const double lat, const double lon)
            onLongTap: {
                navigationInfoPopup.show(lat, lon)
                // todo open dialog with info and option to create a route to the mark
                // use locationinfomodel here
            }

            ColumnLayout {
                id: dialogBtnColumn
                spacing: 20

                anchors.left: parent.left
                anchors.top: parent.top
                anchors.leftMargin: 8
                anchors.topMargin: 45

                RectangleButton {
                    id: btnHistory
                    label: "\u2605"
                    onClicked: {} // todo open history dialog
                }

                RectangleButton {
                    id: btnFavourites
                    label: "\u2764"
                    onClicked: {} // todo
                }

                RectangleButton {
                    id: btnSearch
                    label: "\u2315"
                    onClicked: navigationSearchPopup.visible = true
                }

                RectangleButton {
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

    NavigationSearch {
        id: navigationSearchPopup
        visible: false
    }
}
