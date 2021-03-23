import QtQuick 2.4
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

WarningNotificationForm {
    id: root
    property alias message: root.message
    signal closeNotification
    Layout.fillWidth: true
    Layout.preferredHeight: 50

    Connections {
        target: closeButton
        function onClicked() {
            closeNotification()
        }
    }
}
