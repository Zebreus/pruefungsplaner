import QtQuick 2.4
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

Rectangle {
    width: 1000
    height: 600

    RowLayout {
        id: rowLayout
        anchors.fill: parent

        Rectangle {
            id: rectangle
            color: "#acacac"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        ColumnLayout {
            id: columnLayout
            Layout.maximumWidth: 700
            Layout.leftMargin: 50
            Layout.rightMargin: 50
            Layout.fillHeight: true

            Item {
                id: topFiller
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredHeight: 6
            }

            Image {
                id: image
                Layout.preferredHeight: 13
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
                fillMode: Image.PreserveAspectFit
                source: "qrc:/images/fbi.svg"
                Layout.preferredWidth: parent.width * 0.8
            }

            Label {
                id: label
                text: qsTr("Wilkommen beim Prüfungsplaner")
                font.pointSize: 15
                Layout.preferredHeight: 5
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }

            ColumnLayout {
                id: columnLayout1
                width: 100
                height: 100
                Layout.preferredHeight: 40
                Layout.fillHeight: true

                ColumnLayout {
                    id: usernameColumn
                    Layout.fillWidth: true
                    Layout.rightMargin: parent.width * 0.25
                    Layout.leftMargin: parent.width * 0.25
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                    Label {
                        id: usernameLabel
                        color: "#484848"
                        text: qsTr("Nutzername")
                        font.pointSize: 9
                    }

                    TextField {
                        id: usernameField
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        placeholderText: ""
                    }
                }

                ColumnLayout {
                    id: passwordColumn
                    Layout.fillWidth: true
                    Layout.rightMargin: parent.width * 0.25
                    Layout.leftMargin: parent.width * 0.25
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                    Label {
                        id: passwordLabel
                        color: "#484848"
                        text: qsTr("Passwort")
                        font.pointSize: 9
                    }

                    TextField {
                        id: passwordField
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        placeholderText: ""
                    }
                }

                Button {
                    id: button
                    text: qsTr("Login")
                    Layout.topMargin: 10
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                }
            }

            Item {
                id: bottomFiller
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredHeight: 8
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/

