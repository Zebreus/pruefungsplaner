import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.3

import org.pruefungsplaner.Backend 1.0

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
                icon.name: "build"
                icon.source: "qrc:/icons/material/build-24px.svg"
            }

            ProgressBar {
                id: buildProgress
                from: 0
                to: 100
                value: Backend.progress
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



