import Qt.labs.settings 1.0
import Qt.labs.platform 1.1

Settings {
    id: videoSettings
    category: "video"
    property string directory: StandardPaths.writableLocation(StandardPaths.MoviesLocation)
    property int volume: 30
    property string lastMovie: ""
}
