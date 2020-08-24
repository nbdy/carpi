import QtQuick 2.15
import QtQuick.Controls 2.15
import QtMultimedia 5.15

import settings 1.0

Page {
    id: mediaVideo
    title: qsTr("Video")

    VideoSettings {
        id: videoSettings
    }

    VideoChooser {
        id: videoChooser
        visible: false
        videoSettings: videoSettings
        onBtnVideoSelectedClicked: {
            mediaPlayer.source = selectedVideoUrl
            videoSettings.lastVideo = selectedVideoUrl
        }
    }

    MediaPlayer {
        id: mediaPlayer
        videoOutput: vOut
    }

    Label {
        id: lblVideoUrl
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.left: volumeSlider.right
        anchors.leftMargin: 16
    }

    Slider {
        id: volumeSlider
        orientation: Qt.Vertical
        value: 20 // todo set via settings
        from: 0
        to: 100
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 8
        anchors.topMargin: 8
        anchors.bottom: playPause.top
        anchors.bottomMargin: 8

        onMoved: {
            mediaPlayer.volume = value / 100;
            videoSettings.volume = value;
        }
    }

    Button {
        id: openFileDialogButton
        width: 100
        height: 100
        text: "open" // todo folder icon
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4

        onClicked: videoChooser.visible = true
    }

    Button {
        id: playPause
        text: ">"

        width: 100
        height: 100

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        anchors.left: openFileDialogButton.right
        anchors.leftMargin: 4

        onClicked: {
            text = text == ">" ? "||" : ">"
            // todo start stop video
        }
    }

    Slider {
        id: progress
        from: 0
        to: mediaPlayer.duration
        anchors.left: playPause.right
        anchors.leftMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.verticalCenter: playPause.verticalCenter

        onMoved: mediaPlayer.seek(progress.value)
    }

    VideoOutput {
        id: vOut
        anchors.top: lblVideoUrl.bottom
        anchors.topMargin: 4
        anchors.left: volumeSlider.right
        anchors.leftMargin: 8
        anchors.bottom: progress.top
        anchors.bottomMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 4
    }
}
