import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

// todo set maximumValue via settings (faster cars)
// even though they probably won't even use this since they have their own proper dashboard

CircularGauge {
    maximumValue: 200

    style: CircularGaugeStyle {
        needle: Rectangle {
            y: outerRadius * 0.15
            implicitWidth: outerRadius * 0.03
            implicitHeight: outerRadius * 0.9
            antialiasing: true
            color: "#424242"
        }

        labelStepSize: 20
    }
}
