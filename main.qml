import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2


ApplicationWindow {
    visible: true
    width: 1920
    height: 1080
    title: qsTr("Prüfungsplaner")
    //minimumWidth: column.minimumWidth

    ApplicationManager{}

/*
    property var settingsModel: [
        {
            "name": "PAD1",
            "number": "30.1234",
            "origin": "FBI",
            "groups": [
                "bachelor 1 a",
                "bachelor 1 b",
                "bachelor 1 a",
                "bachelor 1 b",
                "bachelor 1 a",
                "bachelor 1 b",
                "bachelor 1 a",
                "bachelor 1 b",
                "bachelor 1 a",
                "bachelor 1 b",
                "bachelor 1 c"
            ],
            "constraints": [
                "woche 1"
            ],
            "active": true
        },
        {
            "name": "PAD2",
            "number": "30.5353",
            "origin": "FBI",
            "groups": [
                "bachelor 2 a",
                "bachelor 2 b"
            ],
            "constraints": [
                "woche 2"
            ],
            "active": true
        },
        {
            "name": "Grundlagen der Analysis",
            "number": "30.5345",
            "origin": "MN",
            "groups": [
                "bachelor 4 a",
                "bachelor 4 b"
            ],
            "constraints": [
            ],
            "active": false
        },
    ]
    Flickable{
        id: flickable
        flickableDirection: Flickable.VerticalFlick
        anchors.fill: parent
        contentHeight: root.implicitHeight
        boundsBehavior: Flickable.DragOverBounds

        Pane {
            id: root
            anchors.fill: parent

            Column {
                id: column
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.fill: parent
                Layout.fillWidth: true

                Repeater {
                    id: examList
                    model: settingsModel
                    anchors.fill: parent
                    delegate: ExamListItem {
                    }

                }
            }
        }
    }
    */
}
