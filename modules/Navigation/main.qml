import QtQuick 2.12
import QtQuick.Window 2.12
import GeneralMagic 1.0

Window {
  visible: true
  width: 640; height: 480
  title: qsTr("Minimal Map")

  MapView {
    id: mapView
    anchors.fill: parent
  }

  Component.onCompleted: {
    ServicesManager.commonSettings.allowInternetConnection = true;
    ServicesManager.contentManager.autoUpdate = true;
  }
}
