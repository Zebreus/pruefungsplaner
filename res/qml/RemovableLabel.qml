import QtQuick 2.4

RemovableLabelForm {
    id: root
    property var text
    signal removeClicked
    signal clicked

    nameLabel.text: text
    removeMouseArea.onClicked: removeClicked()
    nameMouseArea.onClicked: clicked()

    nameMouseArea.onExited: root.state = ""
    nameMouseArea.onEntered: root.state = "name hover"
    removeMouseArea.onExited: root.state = ""
    removeMouseArea.onEntered: root.state = "remove hover"
}
