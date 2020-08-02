import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.settings 1.0

Page {
    title: "Settings :: Navigation"
    id: settingsUI

    Settings {
        id: navigationSettings
        category: "navigation"
        property string directory: "~/maps/"
        property double lastLatitude: 48.1371
        property double lastLongitude: 11.5761
        property string theme: "light"
    }

    Component.onCompleted: {
        console.log("Navigation")
        console.log(navigationSettings.directory)
        console.log(navigationSettings.lastLatitude)
        console.log(navigationSettings.lastLongitude)
        console.log(navigationSettings.theme)
    }
}
