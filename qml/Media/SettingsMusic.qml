import ".."

RSettings {
    group: "music"

    property string lastSong: get("lastSong").toString()
    property string lastAlbum: get("lastAlbum").toString()
    property double volume: get("volume").toDouble()
    property string directory: get("directory").toString()
}
