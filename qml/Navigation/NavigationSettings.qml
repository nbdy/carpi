import ".."

RSettings {
    onSubscriberConnectedChanged: group = "navigation"

    property double destinationLatitude: -1
    property double destinationLongitude: -1
    property bool route: false
}
