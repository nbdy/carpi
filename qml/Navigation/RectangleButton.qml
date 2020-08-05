import QtQuick 2.0

Rectangle {
    id: rectangleButton

    property color defaultColor: "black"
    property color hoverColor: Qt.lighter(defaultColor, 1.1)
    property string label
    property alias font: rectangleButtonLabel.font
    property int textRotation: 0

    signal clicked

    color: defaultColor
    border.color: "gray"
    border.width: 1
    opacity: 0.8
    width: 60
    height: 60

    MouseArea {
        id: rectangleButtonMouseArea
        anchors.fill: parent

        hoverEnabled: true

        onEntered: parent.color = hoverColor

        onExited: parent.color = defaultColor

        onClicked: parent.clicked()
    }

    Text {
        id: rectangleButtonLabel
        anchors.centerIn: parent
        color: "white"
        text: label
        rotation: textRotation
        font.pointSize: 24
    }

    scale: rectangleButtonMouseArea.pressed ? 1.2 : 1.0

    Behavior on scale {
        NumberAnimation {
            duration: 55
        }
    }
}
