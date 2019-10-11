import QtQuick 2.3
import QtGraphicalEffects 1.0

ListView {
    id: root

    orientation: Qt.Horizontal
    spacing: 3

    delegate: Rectangle {
        color: getColor(modelData)
        width: 10
        height: 10
        radius: 5
        border.color: "white"
        border.width: 1
        Text {
            text: modelData
            anchors.centerIn: parent
            font.pixelSize: parent.height * 0.75
            color: "white"
        }
    }

    function getColor(n) {
        switch(n) {
        case 1: return "grey";
        case 2: return "green";
        case 3: return "purple";
        case 4: return "blue";
        case 5: return "yellow";
        case 6: return "red";
        case 7: return "orange";
        default: return "white";
        }
    }
}
