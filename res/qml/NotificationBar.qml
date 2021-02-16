import QtQuick 2.4
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

NotificationBarForm {
    id: notificationBar
    Layout.fillWidth: true
    Layout.alignment: Qt.AlignTop
    spacing: 0

    Component {
        id: errorNotification
        ErrorNotification {
            id: errorNotificationObject
            NumberAnimation on Layout.preferredHeight {
                id: closeAnimation
                duration: 100
                to: 0
                easing.type: Easing.InOutQuad
                running: false
            }
            Connections {
                function onCloseNotification() {
                    clip = true
                    closeAnimation.start()
                    errorNotificationObject.destroy(100)
                }
            }
        }
    }

    function addErrorNotification(message) {
        errorNotification.createObject(notificationBar, {
                                           "message": message
                                       })
    }
}
