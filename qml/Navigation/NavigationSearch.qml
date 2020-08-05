import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import io.eberlein.carpi.map 1.0

// todo only show items that match the input
// todo close popup and show destination point

Popup {
    id: navigationSearchPopup
    modal: true
    width: 400
    height: 600

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    LocationListModel {
        id: suggestionModel
        resultLimit: 3
    }

    LocationInfoModel {
        id: locationInfoModel

        onFoundLocationInfo: {
            lblPostal.text = postal
            lblCity.text = city
            lblStreet.text = street
            lblHouseNr.text = houseNr
            lblTitle.text = street + " " + houseNr
        }
    }

    contentItem: Item {
        anchors.fill: parent

        Label {
            id: lblAddress
            text: "Search Address:"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 8
            anchors.topMargin: 8
        }

        TextInput {
            id: teAddress
            width: 300
            color: "white"
            anchors.left: lblAddress.right
            anchors.top: parent.top
            anchors.leftMargin: 4
            anchors.topMargin: 8
        }

        Label {
            id: lblSearchState
            text: "Search state:"
            anchors.left: parent.left
            anchors.top: lblAddress.bottom
            anchors.leftMargin: 8
            anchors.topMargin: 4
        }

        Label {
            id: lblSearchStateValue
            text: suggestionModel.searching ? "searching" : "idle"
            anchors.left: lblSearchState.right
            anchors.leftMargin: 4
            anchors.top: lblAddress.bottom
            anchors.topMargin: 4
        }

        Button {
            id: btnSearch
            text: "Search"

            anchors.left: parent.left
            anchors.top: lblSearchState.bottom
            anchors.leftMargin: 8
            anchors.topMargin: 4

            onClicked: suggestionModel.setPattern(teAddress.text)
        }

        Label {
            id: lblResults
            text: "Results:"
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.top: btnSearch.bottom
            anchors.topMargin: 16
        }

        ListView {
            id: suggestionView
            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.top: lblResults.bottom
            anchors.topMargin: 4
            height: 200

            model: suggestionModel
            highlight: Rectangle {border.color: "black"; border.width: 2; color: "#00000000"; radius: 3}
            delegate: searchItemDelegate

            Component {
                id: searchItemDelegate
                Item {
                    height: 30
                    width: 384

                    Label {
                        id: lblLabel
                        text: label
                        font.pointSize: 14
                        anchors.left: parent.left
                        anchors.leftMargin: 8
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: suggestionView.currentIndex = index
                    }
                }
            }

            onCurrentItemChanged: {
                var l = suggestionModel.get(currentIndex)
                locationInfoModel.setLocation(l.lat, l.lon)
            }
        }

        Label {
            id: lblSelectedInfo
            text: "Info:"
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.top: suggestionView.bottom
            anchors.topMargin: 8
        }

        Label {
            id: lblPostal
            anchors.left: lblSelectedInfo.left
            anchors.top: lblSelectedInfo.bottom
            anchors.topMargin: 16
        }

        Label {
            id: lblCity
            anchors.left: lblPostal.right
            anchors.leftMargin: 4
            anchors.top: lblPostal.top
        }

        Label {
            id: lblStreet
            anchors.left: lblSelectedInfo.left
            anchors.top: lblCity.bottom
            anchors.topMargin: 4
        }

        Label {
            id: lblHouseNr
            anchors.left: lblStreet.right
            anchors.leftMargin: 4
            anchors.top: lblStreet.top
        }
    }
}
