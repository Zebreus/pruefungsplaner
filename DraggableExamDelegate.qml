import QtQuick 2.4

DraggableExamDelegateForm {
    Drag.active: dragMouseArea.drag.active

    dragMouseArea{
        drag.target: dragItem
        onPressed: {
            dragItem.startingPosition = Qt.point(dragItem.x, dragItem.y)
        }
        onReleased: {
            print(dragItem.Drag.target)
            dragItem.Drag.proposedAction = Qt.MoveAction

            if ( dragItem.Drag.drop() != Qt.MoveAction) {
                backAnimX.from = dragItem.x
                backAnimX.to = dragItem.startingPosition.x
                backAnimY.from = dragItem.y
                backAnimY.to = dragItem.startingPosition.y
                backAnim.start()
            }
        }
    }

    ParallelAnimation {
        id: backAnim
        SpringAnimation {
            id: backAnimX
            target: dragItem
            property: "x"
            duration: 300
            spring: 4
            damping: 0.3
        }
        SpringAnimation {
            id: backAnimY
            target: dragItem
            property: "y"
            duration: 300
            spring: 4
            damping: 0.3
        }
    }
}
