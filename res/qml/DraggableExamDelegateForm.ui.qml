import QtQuick 2.4
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3

Item {
    id: dragItem
    width: content.implicitWidth
    height: content.implicitHeight
    property point startingPosition
    property alias dragMouseArea: dragMouseArea
    property alias dragItem: dragItem
    property alias text: label.text
    //color: "#7548e2ea"

    z: dragMouseArea.drag.active || dragMouseArea.pressed ? 2 : 1
    MouseArea {
        id: dragMouseArea
        anchors.fill: parent
    }

    RowLayout {
        id: content
        Label {
            id: label
            text: "PLACEHOLDER"
        }
    }
}
