import Qt.labs.platform 1.1
import ".."

RSettings {
    onSubscriberConnectedChanged: group = "music"
    onClientConnectedChanged: {
        set("lastSong", "")
        set("lastAlbum", "")
        set("directory", StandardPaths.writableLocation(StandardPaths.MusicLocation))
        set("volume", 42)
    }
}
