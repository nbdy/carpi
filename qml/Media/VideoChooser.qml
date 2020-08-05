import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Popup {
    id: videoChooserPopup
    modal: true
    width: 400
    height: 600
    anchors.centerIn: parent

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    contentItem: Item {

    }
}
