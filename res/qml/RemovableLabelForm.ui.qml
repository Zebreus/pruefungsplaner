import QtQuick 2.4
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.14
import QtQuick.Controls.Material 2.0
import QtGraphicalEffects 1.12

Item {
    id: root
    width: rectangle.width
    height: rectangle.height

    property alias nameMouseArea: nameMouseArea
    property alias removeMouseArea: removeMouseArea
    property alias nameLabel: nameLabel

    SystemPalette {
        id: myPalette
        colorGroup: SystemPalette.Active
    }

    Rectangle {
        id: rectangle
        width: rowLayout.width
        height: rowLayout.height
        radius: 8
        clip: false
        border.width: 0
        color: myPalette.midlight

        Row {
            id: rowLayout
            spacing: 0
            Layout.margins: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            Item {
                id: nameElement
                width: nameLabel.width
                height: nameLabel.height
                clip: true

                ColorOverlay {
                    id: nameColor
                    width: rectangle.width
                    height: rectangle.height
                    source: rectangle
                    color: myPalette.midlight
                }

                Label {
                    id: nameLabel
                    text: "placeholder"
                    padding: 2
                    color: myPalette.buttonText
                    leftPadding: 4
                }

                MouseArea {
                    id: nameMouseArea
                    hoverEnabled: true
                    anchors.fill: parent
                }
            }

            Item {
                id: removeElement
                width: nameLabel.height
                height: nameLabel.height
                Layout.alignment: Qt.AlignLeft
                clip: true

                ToolButton {
                    id: removeLabel
                    anchors.fill: parent
                    padding: 1
                    icon.name: "clear"
                    icon.source: "qrc:/icons/material/clear-24px.svg"
                    icon.color: myPalette.buttonText
                    Layout.preferredWidth: parent.width * 0.8
                }

                MouseArea {
                    id: removeMouseArea
                    hoverEnabled: true
                    anchors.fill: parent
                }
            }
        }
    }

    states: [
        State {
            name: "name hover"

            PropertyChanges {
                target: nameLabel
                color: myPalette.midlight
            }

            PropertyChanges {
                target: nameColor
                color: "#373737"
            }
        },
        State {
            name: "remove hover"

            PropertyChanges {
                target: removeLabel
                icon.color: myPalette.midlight
            }

            PropertyChanges {
                target: rectangle
                color: "#373737"
            }
        }
    ]
}
