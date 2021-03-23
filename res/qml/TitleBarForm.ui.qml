import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.3

ToolBar {
    position: ToolBar.Header
    property alias scheduleGoodMenuItem: scheduleGoodMenuItem
    property alias scheduleFastMenuItem: scheduleFastMenuItem
    property alias buildButtonMenu: buildButtonMenu
    property alias buildButtonMouseArea: buildButtonMouseArea

    id: toolBar
    property alias planSelector: planSelector
    property alias semesterSelector: semesterSelector
    property alias resultButton: resultButton
    property alias buildProgress: buildProgress
    property alias buildButton: buildButton
    property alias overviewButton: overviewButton
    property alias menuButton: menuButton
    bottomPadding: 5
    topPadding: 5

    width: 1980
    height: 100

    RowLayout {
        id: row
        anchors.fill: parent

        RowLayout {
            ToolButton {
                id: menuButton
                display: AbstractButton.IconOnly
                icon.name: "menu"
                icon.source: "qrc:/icons/material/menu-24px.svg"
            }

            Image {
                id: image
                source: "qrc:/images/fbi.svg"
                fillMode: Image.PreserveAspectFit
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: paintedWidth
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Label {
                //: Application name
                text: qsTr("Prüfungsplaner")
                font.pointSize: 20
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignLeft
            Layout.fillWidth: true
            ComboBox {
                id: semesterSelector
                textRole: "name"
                Layout.preferredWidth: 250
            }

            ComboBox {
                id: planSelector
                textRole: "name"
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignRight

            ToolButton {
                id: overviewButton
                display: AbstractButton.IconOnly
                icon.name: "dashboard"
                icon.source: "qrc:/icons/material/dashboard-24px.svg"
                icon.color: "transparent"
            }

            ToolButton {
                id: buildButton
                display: AbstractButton.IconOnly
                icon.name: "play_arrow"
                icon.source: "qrc:/icons/material/play_arrow-24px.svg"
                MouseArea {
                    id: buildButtonMouseArea
                    anchors.fill: parent
                    acceptedButtons: Qt.RightButton
                }
                Menu {
                    id: buildButtonMenu

                    MenuItem {
                        id: scheduleFastMenuItem
                        text: qsTr("Schnelle Planung")
                    }
                    MenuItem {
                        id: scheduleGoodMenuItem
                        text: qsTr("Gute Planung")
                    }
                }
            }

            ProgressBar {
                id: buildProgress
                from: 0
                to: 100
                value: 0
            }

            ToolButton {
                id: resultButton
                display: AbstractButton.IconOnly
                icon.name: "event"
                icon.source: "qrc:/icons/material/event-24px.svg"
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/

