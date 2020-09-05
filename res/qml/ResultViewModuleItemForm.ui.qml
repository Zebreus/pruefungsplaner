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
            //: Button to move item
            text: qsTr("Verschieben", "move action")
            flat: false
            icon.name: "drag_indicator"
            icon.source: "qrc:/icons/material/drag_indicator-24px.svg"
            display: AbstractButton.IconOnly
        }

        Popup {
            id: moduleEditorPopup
            dim: true
            modal: true
            focus: true
            anchors.centerIn: Overlay.overlay
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
            DateEditor {
                id: dateEditorPopup
                module: dataModel
            }
        }

        Connections {
            target: moveButton
            onClicked: moduleEditorPopup.open()
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

