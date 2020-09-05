import QtQuick 2.4
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.14
import QtQuick.Controls.Material 2.0
import QtGraphicalEffects 1.12

Item {
    property string myText
    signal removeClicked
    signal clicked

    SystemPalette {
        id: myPalette
        colorGroup: SystemPalette.Active
    }
    id: root
    width: rectangle.width
    height: rectangle.height

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
                    text: qsTr(myText)
                    padding: 2
                    color: myPalette.buttonText
                    leftPadding: 4
                }

                MouseArea {
                    id: nameMouseArea
                    hoverEnabled: true
                    anchors.fill: parent
                }

                Connections {
                    target: nameMouseArea
                    onClicked: root.clicked()
                }
            }

            Item {
                id: removeElement
                width: removeLabel.width
                height: nameLabel.height
                Layout.alignment: Qt.AlignLeft
                clip: true

                Label {
                    id: removeLabel
                    text: ""
                    padding: 2
                    color: myPalette.buttonText
                    rightPadding: 4
                }

                MouseArea {
                    id: removeMouseArea
                    hoverEnabled: true
                    anchors.fill: parent
                }

                Connections {
                    target: removeMouseArea
                    onClicked: root.removeClicked()
                }
            }
        }
    }

    Connections {
        target: nameMouseArea
        onExited: {
            root.state = ""
        }
        onEntered: {
            root.state = "name hover"
        }
    }

    Connections {
        target: removeMouseArea
        onExited: {
            root.state = ""
        }
        onEntered: {
            root.state = "remove hover"
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
                color: myPalette.midlight
            }

            PropertyChanges {
                target: rectangle
                color: "#373737"
            }
        }
    ]
}
