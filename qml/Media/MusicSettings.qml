import Qt.labs.settings 1.0
import Qt.labs.platform 1.1

Settings {
    id: musicSettings
    category: "music"
    property string directory: StandardPaths.writableLocation(StandardPaths.MusicLocation)
    property int volume: 30
    property string lastSong: ""
    property string lastAlbum: ""
}
