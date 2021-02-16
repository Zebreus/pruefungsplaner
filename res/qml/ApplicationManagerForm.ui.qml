import QtQuick 2.4
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Item {
    width: 1920
    height: 1080
    property alias stackLayout: stackLayout
    property alias titleBar: titleBar
    property alias notificationBar: notificationBar

    ShaderEffectSource {
        id: effectSource
        sourceItem: background
        anchors.fill: parent
        sourceRect: Qt.rect(x, y, width, height)
    }

    Rectangle {
        id: background
        anchors.fill: parent
        color: "white"
        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            RowLayout {
                id: rowLayout
                Layout.fillWidth: true
                Layout.minimumHeight: 40

                TitleBar {
                    id: titleBar
                    Layout.fillWidth: true
                }
            }

            NotificationBar {
                id: notificationBar
                Layout.fillWidth: true
                Layout.margins: 0
            }

            StackLayout {
                id: stackLayout
                Layout.fillHeight: true
                Layout.fillWidth: true

                currentIndex: 0

                PlanningView {
                    id: planningView
                }

                ResultView {
                    id: resultView
                }
            }
        }
    }

    LoginPopup {
        width: 1000
        height: 500
        backgroundSource: effectSource
        visible: true
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.25}
}
##^##*/

