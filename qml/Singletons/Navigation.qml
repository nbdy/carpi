import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtPositioning 5.6

import io.eberlein.carpi.map 1.0
import settings 1.0


GridLayout {
    NavigationSettings {
        id: settings
    }

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
}
