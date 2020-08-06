import Qt.labs.settings 1.0
import Qt.labs.platform 1.1

Settings {
    id: navigationSettings
    category: "navigation"
    property double destinationLatitude: -1
    property double destinationLongitude: -1
    property bool route: false
}
