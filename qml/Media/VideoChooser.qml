import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.folderlistmodel 2.15

import settings 1.0

Popup {
    id: videoChooserPopup
    modal: true
    width: 400
    height: 400
    anchors.centerIn: parent

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    property VideoSettings videoSettings

    property string selectedVideoUrl
    signal btnVideoSelectedClicked

    FolderListModel {
        id: videoModel
        showDirs: false
        showFiles: true
        nameFilters: ["*.mp4", "*.avi", "*.mpeg"]
        folder: videoSettings.directory
    }

    contentItem: Item {
        Button {
            id: btnSelectVideo
            onClicked: btnVideoSelectedClicked()
            text: "Select"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 4
            anchors.right: parent.right
            anchors.rightMargin: 4
        }

        ListView {
            id: videoListView

            anchors.left: parent.left
            anchors.top: parent.top
            anchors.right: parent.right
            model: videoModel

            highlight: Rectangle {border.color: "black"; border.width: 2; color: "#00000000"; radius: 3}
            delegate: videoItemDelegate

            Component {
                id: videoItemDelegate
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
                        onClicked: videoListView.currentIndex = index
                    }
                }
            }

            onCurrentItemChanged: {
                selectedVideoUrl = videoModel.get(currentIndex, "fileUrl")
            }
        }
    }
}
