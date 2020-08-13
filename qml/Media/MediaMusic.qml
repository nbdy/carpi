import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.folderlistmodel 2.15
import Qt.labs.platform 1.0
import QtMultimedia 5.15
import QtQuick.Controls.Material 2.12

import settings 1.0
import io.eberlein.disqt 1.0

// todo folder browser for albums / music

Page {
    id: mediaMusic
    title: qsTr("Music")

    Component.onCompleted: {
        if(musicSettings.lastAlbum !== "") loadAlbum(musicSettings.lastAlbum)
        if(musicSettings.lastSong !== "") mediaPlayer.playlist.addItem(musicSettings.lastSong)
    }

    MusicSettings {
        id: musicSettings

        redis: Redis {
            onClientIsConnectedChanged: console.log("client connected to redis")
            onSubscriberIsConnectedChanged: console.log("subscriber connected to redis")
        }

        onReady: {
            console.log("MusicSettings:")
            console.log(" directory:", directory)
            console.log(" volume:", volume)
            console.log(" lastAlbum:", lastAlbum)
            console.log(" lastSong:", lastSong)
            if(directory === undefined) directory = StandardPaths.writableLocation(StandardPaths.MusicLocation)
        }
    }

    FolderListModel {
        id: albumModel
        showDirs: false
        showFiles: true
        nameFilters: ["*.mp3"]
    }

    function loadSong(f) {
        console.log("loading song: ", f)
        mediaPlaylist.addItem(f)
    }

    function loadAlbum(f){
        if(f === undefined) return;
        console.log("loading album: ", f)
        albumModel.folder = f
        for(var i=0; i<albumModel.count; i++) loadSong(albumModel.get(i, "fileUrl"))
    }

    function getAlbumCover(){ // todo load via qquickimageprovider & id3lib or via use a cpp mediaplayer and use qmediametadata and access coverartimage
        var m = mediaPlayer.metaData
        if(m.coverArtUrlLarge) return m.coverArtUrlLarge
        else if(m.coverArtUrlSmall) return m.coverArtUrlSmall
        else if(m.posterUrl) return m.posterUrl
        else if(m.coverArtImage) return m.coverArtImage
        return "qrc:///img/cover.png"
    }

    function strOrNothing(s){
        if(s === undefined) return ""
        return s
    }

    Playlist {
        id: mediaPlaylist
    }

    MediaPlayer {
        id: mediaPlayer
        playlist: mediaPlaylist
        volume: musicSettings.volume / 100
    }

    Label {
        id: lblArtist
        anchors.bottom: lblAlbum.top
        anchors.bottomMargin: 4
        anchors.left: parent.left
        anchors.leftMargin: 4
        text: strOrNothing(mediaPlayer.metaData.albumArtist)
    }

    Label {
        id: lblAlbum
        anchors.bottom: lblSong.top
        anchors.bottomMargin: 4
        anchors.left: parent.left
        anchors.leftMargin: 4
        text: strOrNothing(mediaPlayer.metaData.albumTitle)
    }

    Label {
        id: lblSong
        anchors.bottom: songProgress.top
        anchors.bottomMargin: 16
        anchors.left: parent.left
        anchors.leftMargin: 4
        text: strOrNothing(mediaPlayer.metaData.title)
    }

    Image {
        id: imgCover
        fillMode: Image.PreserveAspectFit
        anchors.left: btnLastSong.left
        anchors.right: btnPlayPause.right
        anchors.top: parent.top
        anchors.bottom: lblArtist.top
        anchors.bottomMargin: 16
        source: getAlbumCover()
    }

    Slider {
        id: songProgress
        anchors.left: btnLastSong.left
        anchors.bottom: btnPlayPause.top
        anchors.right: btnNextSong.right
        value: mediaPlayer.position
        to: mediaPlayer.duration

        onMoved: {
            mediaPlayer.seek(songProgress.position)
        }
    }

    Label {
        id: lblSongProgressSpacer
        text: "/"
        anchors.left: lblSongProgress.right
        anchors.bottom: lblSongProgress.bottom
        anchors.leftMargin: 4
    }

    Label {
        id: lblSongProgress
        text: "0:00"
        anchors.top: songProgress.top
        anchors.left: songProgress.right
        anchors.leftMargin: -(lblSongProgress.implicitWidth + lblSongProgressSpacer.implicitWidth + lblSongLength.implicitWidth)
    }

    Label {
        id: lblSongLength
        text: "10:00"
        anchors.left: lblSongProgressSpacer.right
        anchors.bottom: lblSongProgressSpacer.bottom
        anchors.leftMargin: 4
    }

    Slider {
        id: volumeSlider
        orientation: Qt.Vertical
        anchors.left: btnPlayPause.right
        anchors.rightMargin: 16
        anchors.top: parent.top
        anchors.topMargin: 32
        height: 300
        to: 100
        value: musicSettings.volume

        onMoved: {
            var cv = volumeSlider.value
            if(cv >= 90) lblVolumeMax.visible = false
            else lblVolumeMax.visible = true
            if(cv <= 10) lblVolumeMin.visible = false
            else lblVolumeMin.visible = true

            musicSettings.volume = volumeSlider.value
            mediaPlayer.volume = volumeSlider.value / 100
        }
    }

    Label {
        id: lblVolume
        anchors.bottom: volumeSlider.top
        anchors.left: volumeSlider.left
        text: "Volume"
    }

    function calculatePosition(v) {
        return v / 100 * volumeSlider.height
    }

    Label {
        id: lblVolumeCurrent
        anchors.left: volumeSlider.right
        anchors.bottom: volumeSlider.bottom
        text: volumeSlider.value | 0
        anchors.bottomMargin: calculatePosition(volumeSlider.value)
    }

    Label {
        id: lblVolumeMax
        anchors.left: volumeSlider.right
        anchors.top: volumeSlider.top
        text: "100"
    }

    Label {
        id: lblVolumeMin
        anchors.left: volumeSlider.right
        anchors.bottom: volumeSlider.bottom
        text: "0"
    }

    Button {
        id: btnLastSong
        text: "<<"
        width: 200
        height: 100
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        anchors.left: parent.left
        anchors.leftMargin: 4

        onClicked: {
            var p = mediaPlayer.playlist
            if(p.currentIndex >= 0) p.previous()
        }
    }

    Button {
        id: btnPlayPause
        text: ">"
        width: 200
        height: 100
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        anchors.left: btnLastSong.right
        anchors.leftMargin: 4

        onClicked: {
            if(mediaPlaylist.itemCount == 0) return;

            var s = mediaPlayer.playbackState
            if(s === MediaPlayer.PlayingState) {
                btnPlayPause.text = ">"
                mediaPlayer.pause()
            } else {
                btnPlayPause.text = "||"
                mediaPlayer.play()
            }
        }
    }

    Button {
        id: btnNextSong
        text: ">>"
        width: 200
        height: 100
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        anchors.left: btnPlayPause.right
        anchors.leftMargin: 4

        onClicked: {
            var p = mediaPlayer.playlist
            console.log("current index: ", p.currentIndex, "; itemCount: ", p.itemCount)
            if(p.currentIndex < p.itemCount) p.next()
        }
    }

    ListView {
        id: folderList
        anchors.left: btnNextSong.right
        anchors.leftMargin: 16
        anchors.top: parent.top
        anchors.topMargin: 4
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        model: folderModel

        FolderListModel {
            id: folderModel
            showDirs: true
            showFiles: false
            folder: musicSettings.directory
        }

        highlight: Rectangle {border.color: "black"; border.width: 2; color: "#00000000"; radius: 3}
        delegate: searchItemDelegate

        Component {
            id: searchItemDelegate
            Item {
                height: 30
                width: folderList.width

                Label {
                    text: fileName
                    font.pointSize: 14
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: folderList.currentIndex = index
                }
            }
        }

        onCurrentItemChanged: {
            if(folderModel.isFolder(currentIndex)) loadAlbum(folderModel.get(currentIndex, "fileUrl"))
        }
    }
}
