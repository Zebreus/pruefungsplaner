import QtQuick 2.4
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Item {
    //Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
    //id: columnLayout45
    property alias modulesRepeater: modulesRepeater
    implicitWidth: modulesColumn.implicitWidth
    implicitHeight: modulesColumn.implicitHeight
    //Layout.fillWidth: true


    /*Label {
        //text: modelData.name
        Layout.fillWidth: true
    }*/
    ColumnLayout {
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        id: modulesColumn
        Layout.fillWidth: true
        Repeater {
            id: modulesRepeater
            model: dummysemesters.semesters[0].plans[0].weeks[0].days[0].timeslots[0].modules
            delegate: Label {
                text: modelData.name
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}
}
##^##*/

