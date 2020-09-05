import QtQuick 2.4
import QtQuick.Controls 2.13

import org.pruefungsplaner.Backend 1.0

PlanningViewForm {
    anchors.fill: parent

    Connections {
        target: newGroupMouseArea
        onClicked: {
            //: New group default name
            Backend.activePlan.addNewGroup(qsTr("Gruppe"));
            //console.log(JSON.stringify(Backend.activePlan.weeks[0]));
            //TODO better solution to open popup
            groupList.children[Backend.activePlan.groups.length-1].children[0].children[0].clicked(false);
        }
    }

    Connections {
        target: newConstraintMouseArea
        onClicked: {
            //: New constraint default name
            Backend.activePlan.addNewConstraint(qsTr("Bedingung"));
            //TODO better solution to open popup
            constraintList.children[Backend.activePlan.constraints.length-1].children[0].children[0].clicked(false);
        }
    }

}


