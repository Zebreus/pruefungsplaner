import QtQuick 2.4
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import QtGraphicalEffects 1.0

Popup {
    id: popup
    modal: false
    focus: true
    anchors.centerIn: parent
    padding: 0
    visible: true
    width: columnLayout.width
    height: columnLayout.height

    property var activeGroups
    property alias visibleGroups: groupsRepeater.model
    property alias filterTextField: filterTextField

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    DropShadow {
        anchors.fill: popupBackground
        visible: true
        horizontalOffset: 0
        verticalOffset: 0
        radius: 10
        samples: 5
        color: "black"
        source: popupBackground
    }

    Rectangle {
        id: popupBackground
        color: "white"
        width: popup.width
        height: popup.height
    }

    ColumnLayout {
        id: columnLayout
        spacing: 0

        Label {
            Layout.leftMargin: 20
            Layout.rightMargin: 20
            Layout.topMargin: 15
            Layout.bottomMargin: 10
            id: label
            //: Heading of popup to select groups
            text: qsTr("Gruppe hinzufügen", "popup heading")
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.leftMargin: 10
            Layout.rightMargin: 10
            Layout.bottomMargin: 10
            TextField {
                Layout.fillWidth: true
                Layout.maximumWidth: 300
                id: filterTextField
                //: Placeholder for group filter field
                placeholderText: qsTr(" ", "group filter placeholder")
            }
            Image {
                id: image
                source: "qrc:/icons/material/search-24px.svg"
                fillMode: Image.PreserveAspectFit
                Layout.preferredWidth: parent.height
            }
            MouseArea {
                anchors.fill: parent
                onClicked: filterTextField.focus = true
            }
        }

        GridLayout {
            rows: 10
            flow: GridLayout.TopToBottom
            Layout.rightMargin: 20
            columnSpacing: 0
            rowSpacing: 0
            Repeater {
                id: groupsRepeater

                delegate: CheckBox {
                    id: groupCheckBox
                    Layout.fillWidth: true
                    leftPadding: 10
                    topPadding: 3
                    bottomPadding: 3
                    display: AbstractButton.TextBesideIcon
                    verticalPadding: 0
                    checked: activeGroups.includes(modelData)
                    text: modelData.name
                    Connections {
                        target: groupCheckBox
                        onClicked: {
                            var tempGroups = activeGroups
                            if (groupCheckBox.checked) {
                                tempGroups.push(modelData)
                            } else {
                                tempGroups.splice(tempGroups.indexOf(
                                                      modelData), 1)
                            }
                            activeGroups = tempGroups
                        }
                    }
                }
            }
        }

        Item {
            height: 10
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/

