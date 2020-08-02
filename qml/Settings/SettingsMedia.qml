import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.settings 1.0

Page {
    title: "Settings :: Media"
    id: settingsUI

    Settings {
        id: videoSettings
        category: "video"
        property string directory: "~/Video/"
        property int volume: 30
        property string lastVideo: ""
    }

    Component.onCompleted: {
        console.log("Video")
        console.log(videoSettings.directory)
        console.log(videoSettings.volume)
        console.log(videoSettings.lastVideo)
    }
}
