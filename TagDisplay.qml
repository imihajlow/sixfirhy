/*
    Sixfirhy, a minimalist macos image viewer.
    Copyright (C) 2020 Ivan Mikhailov

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
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
