import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.settings 1.0
import QtQuick.Controls.Material 2.12

Page {
    id: settingsUI

    Settings {
        id: uiSettings
        category: "ui"
        property string theme: Material.Dark
        property int accent: Material.Purple
    }

    Component.onCompleted: {
        console.log("Theme")
        console.log(uiSettings.theme)
        console.log(uiSettings.accent)
    }
}
