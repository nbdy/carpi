import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import QtPositioning 5.6

import net.sf.libosmscout.map 1.0

// todo routing

Page {
    id: navigation
    title: qsTr("Navigation")

    function reroute(){
        var p = gpsSource.position.coordinate
        var s = routingModel.locationEntryFromPosition(p.latitude, p.longitude)
        // todo get target destination
    }

    PositionSource {
        id: gpsSource
        updateInterval: 420 // set via settings
        active: true
        preferredPositioningMethods: PositionSource.SatellitePositioningMethods // set via settings

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
    }

    NavigationModel {
        id: navigationModel
        route: routingModel.route

        onRerouteRequest: {
            if(routingModel.ready) reroute()
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

            Component.onCompleted: {
                var c = gpsSource.position.coordinate
                map.showCoordinates(c.latitude, c.longitude)
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
                    label: "\u2606"
                    onClicked: {} // todo open history dialog
                }

                RectangleButton {
                    id: btnFavourites
                    label: "\u2764"
                    onClicked: {} // todo
                }

                RectangleButton {
                    id: btnSearch
                    label: "\u1F50D"
                    onClicked: {} // todo
                }
            }
        }
    }
}
