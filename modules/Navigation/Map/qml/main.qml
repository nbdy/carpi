import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.1

import QtPositioning 5.12

import net.sf.libosmscout.map 1.0


Rectangle {
    width: 1024
    height: 600

    GridLayout {
        id: content
        anchors.fill: parent

        Map {
            id: map
            Layout.fillWidth: true
            Layout.fillHeight: true
            focus: true
            renderingType: "tiled"

            Location {
                id: nurnberg
                coordinate: QtPositioning.coordinate(49.4352658, 11.0532483);
            }

            function setupInitialPosition(){
                if(map.databaseLoaded){
                    if(map.isInDatabaseBoundingBox(nurnberg)) showCoordinates(nurnberg);

                    console.log("yay?")
                }
                console.log("woo")
            }

            onDatabaseLoaded: {
                setupInitialPosition();
            }
        }
    }
}
