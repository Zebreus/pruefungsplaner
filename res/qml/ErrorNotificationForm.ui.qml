import QtQuick 2.4
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Rectangle {
    property var message: "Ganz schlimmer Fehler! Du solltest was tun."
    property alias closeButton: closeButton
    color: "red"
    width: 1080
    height: 50
    RowLayout {
        anchors.fill: parent
        Label {
            id: errorMessageLabel
            text: message
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }
        Button {
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.rightMargin: 100
            id: closeButton
            text: qsTr("OK")
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/

