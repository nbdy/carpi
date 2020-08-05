import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Shapes 1.15

Item {
    function placeAt(x, y){
        marker.x = x - marker.width / 2
        marker.y = y
        visible = true
    }

    function getWidestWidth(){
        var w = lblTitle.implicitWidth
        if(lblStreet.implicitWidth > w) w = lblStreet.implicitWidth
        else if(lblCity.implicitWidth > w) w = lblCity.implicitWidth
        else if(lblLatitude.implicitWidth > w) w = lblLatitude.implicitWidth
        else if(lblLongitude.implicitWidth > w) w = lblLongitude.implicitWidth
        return w + 20
    }

    function getHeight(){
        return lblTitle.implicitHeight + lblStreet.implicitHeight + lblCity.implicitHeight + lblLatitude.implicitHeight + lblLongitude.implicitHeight + 40
    }

    signal onRouteButtonClicked

    property string title
    property string city
    property string street
    property double latitude
    property double longitude

    Rectangle {
        id: marker
        width: getWidestWidth()
        height: getHeight()
        color: "#33000000"
        radius: 4

        Label {
            id: lblTitle
            text: title
            font.pointSize: 12
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 4
            anchors.leftMargin: 4
        }

        Label {
            id: lblStreet
            text: street
            anchors.top: lblTitle.bottom
            anchors.topMargin: 4
            anchors.left: lblTitle.left
        }

        Label {
            id: lblCity
            text: city
            anchors.top: lblStreet.bottom
            anchors.topMargin: 4
            anchors.left: lblTitle.left
        }

        Label {
            id: lblLatitude
            text: latitude
            anchors.top: lblCity.bottom
            anchors.topMargin: 4
            anchors.left: lblTitle.left
        }

        Label {
            id: lblLongitude
            text: longitude
            anchors.top: lblLatitude.bottom
            anchors.topMargin: 4
            anchors.left: lblTitle.left
        }

        Button {
            id: btnRoute
            text: "Route"
            anchors.top: lblLatitude.top
            anchors.bottom: lblLongitude.bottom
            anchors.right: parent.right
            anchors.rightMargin: 4
            onClicked: onRouteButtonClicked()
        }
    }

    Shape {
        width: marker.width / 5
        height: marker.height / 5
        anchors.horizontalCenter: marker.horizontalCenter
        anchors.top: marker.bottom

        ShapePath {
            strokeWidth: 2
            strokeColor: "black"
            fillColor: "#33000000"
            startX: marker.x + marker.width / 2
            startY: marker.y + marker.height / 10
            PathLine {x: marker.x + marker.width / 2 + marker.width / 10; y: marker.y}
            PathLine {x: marker.x + marker.width / 2 - marker.width / 10; y: marker.y}
            PathLine {x: marker.x + marker.width / 2; y: marker.y + marker.height / 10}
        }
    }
}
