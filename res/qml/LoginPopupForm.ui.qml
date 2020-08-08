import QtQuick 2.4
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import QtGraphicalEffects 1.0

Popup {
    id: loginPopup
    dim: true
    modal: true
    focus: true
    anchors.centerIn: parent
    padding: 0
    //width: myLoginPopup.width
    //height: myLoginPopup.height
    width: 1000
    height: 500
    visible: true

    property alias loginButton: loginButton
    property alias errorLabel: errorLabel
    property alias passwordField: passwordField
    property alias usernameField: usernameField
    property var backgroundSource

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    Overlay.modal: Item {
        FastBlur {
            anchors.fill: parent
            id: blur
            source: backgroundSource
            radius: 32
            cached: false
        }
        ColorOverlay {
            anchors.fill: parent
            id: dim
            source: blur
            color: "#60000000"
        }
    }

    DropShadow {
        width: loginPopup.width
        height: loginPopup.height
        visible: true
        horizontalOffset: 0
        verticalOffset: 0
        radius: 10
        samples: 5
        color: "black"
        source: myLoginPopup
    }

    Rectangle {
        width: parent.width
        height: parent.height
        id: myLoginPopup

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

                ColumnLayout {
                    id: messageColumn
                    //Layout.preferredHeight: 5
                    Layout.minimumHeight: 50
                    Layout.fillHeight: true
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    //Layout.fillWidth: true
                    Layout.preferredWidth: parent.width
                    Label {
                        id: label
                        text: qsTr("Wilkommen beim Prüfungsplaner")
                        font.pointSize: 15
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    }

                    Label {
                        id: errorLabel
                        color: "#dd0000"
                        //text: qsTr("Dein Nutzername und dein Passwort sind nicht korrekt. Bitte überprüfe deine Angaben und versuche es erneut.")
                        wrapMode: Text.WordWrap
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        Layout.preferredWidth: parent.width * 0.65
                    }
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
                        id: loginButton
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
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/

