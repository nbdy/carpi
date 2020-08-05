import Qt.labs.settings 1.0
import Qt.labs.platform 1.1

Settings {
    id: uiSettings
    category: "ui"
    property string theme: Material.Dark
    property int accent: Material.Purple
}
