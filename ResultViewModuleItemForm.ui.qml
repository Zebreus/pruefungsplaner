import QtQuick 2.4
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

ItemDelegate {
    property var dataModel
    checkable: false
    contentItem: RowLayout {
        id: rowLayout

        Label {
            text: dataModel.name
        }

        Button {
            id: moveButton
            text: qsTr("Verschieben")
            flat: false
            icon.name: "drag_indicator"
            icon.source: "res/icons/material/drag_indicator-24px.svg"
            display: AbstractButton.IconOnly
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

