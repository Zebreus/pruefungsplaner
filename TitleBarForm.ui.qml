import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.3
import "dummydata"

ToolBar {
    position: ToolBar.Header

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
    RowLayout {
        id: row
        anchors.fill: parent

        RowLayout {
            ToolButton {
                id: menuButton
                display: AbstractButton.IconOnly
                icon.name: "menu"
                icon.source: "res/icons/material/menu-24px.svg"
            }

            Image {
                id: image
                source: "res/images/fbi.svg"
                fillMode: Image.PreserveAspectFit
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: paintedWidth
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Label {
                text: "Prüfungsplaner"
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
                icon.source: "res/icons/material/dashboard-24px.svg"
                icon.color: "transparent"
            }

            ToolButton {
                id: buildButton
                display: AbstractButton.IconOnly
                icon.name: "build"
                icon.source: "res/icons/material/build-24px.svg"
            }

            ProgressBar {
                id: buildProgress
                from: 0
                to: 1
                value: 0.5
            }

            ToolButton {
                id: resultButton
                display: AbstractButton.IconOnly
                icon.name: "event"
                icon.source: "res/icons/material/event-24px.svg"
            }
        }
    }
}
