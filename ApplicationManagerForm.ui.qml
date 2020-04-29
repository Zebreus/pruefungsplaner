import QtQuick 2.4
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3

Item {
    width: 1920
    height: 1080
    property alias stackLayout: stackLayout
    property alias titleBar: titleBar

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        RowLayout {
            z: 10
            id: rowLayout
            Layout.fillWidth: true
            Layout.minimumHeight: 40

            //Layout.preferredHeight: 40
            //Layout.maximumHeight: 40
            TitleBar {
                id: titleBar
                Layout.fillWidth: true
            }
        }

        StackLayout {
            id: stackLayout
            Layout.fillHeight: true
            Layout.fillWidth: true

            currentIndex: 0

            PlanningView {
                id: planningView
            }

            //ResultView {
            //    id: resultView
            //}
        }
    }
}
