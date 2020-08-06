import QtQuick 2.4
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.14

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

