import QtQuick 2.4
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.14

import org.pruefungsplaner.Backend 1.0

//ItemDelegate {
//    id: delegate
//    checkable: true

//    contentItem:
    ExamListItemForm{
        property alias dataModel: myItemDelegate.myModelData
        //property alias model: myModelData
        width: parent.width
        id: myItemDelegate
        Behavior on realHeight {
            NumberAnimation {
                id: moveAnim
                easing.type: Easing.InOutQuad
                onRunningChanged: {
                      if(!moveAnim.running){
                             console.log("End of transition!");
                      }
                }
            }
        }

        groupPopup.activeGroups: dataModel.groups
        groupPopup.groups: Backend.activePlan.groups
        Connections{
            target: groupPopup
            onActiveGroupsChanged: {
                dataModel.groups = groupPopup.activeGroups;
            }
        }
        Connections{
            target: addGroupButton
            onClicked: myItemDelegate.groupPopup.open();
        }

        constraintPopup.activeGroups: dataModel.constraints
        constraintPopup.groups: Backend.activePlan.constraints
        Connections{
            target: constraintPopup
            onActiveGroupsChanged: {
                dataModel.constraints = constraintPopup.activeGroups;
            }
        }
        Connections{
            target: addConstraintButton
            onClicked: myItemDelegate.constraintPopup.open();
        }
    }
/*    states: [
        State {
            name: "collapsed"
            when: !delegate.checked

            PropertyChanges {
                target: myItemDelegate
                showDetails: false
            }

        },
        State {
            name: "expanded"
            when: delegate.checked

            PropertyChanges {
                target: myItemDelegate
                showDetails: true
            }
        }
    ]
}*/

