import QtQuick 2.4

import org.pruefungsplaner.Backend 1.0

GroupEditorPopupForm {

    property alias group: groupEditor.myGroup
    id: groupEditor

    daysRepeater.model: Backend.activePlan.weeks

    Connections {
        target: categorySelector
        function onActivated(index) {
            switch (index) {
            case 0:
                //active
                group.active = true
                group.small = false
                group.obsolete = false
                break
            case 1:
                //inactive
                group.active = false
                group.small = false
                group.obsolete = false
                break
            case 2:
                //small
                group.active = false
                group.small = true
                group.obsolete = false
                break
            case 3:
                //obsolete
                group.active = false
                group.small = false
                group.obsolete = true
                break
            }
        }
    }

    Connections {
        target: group
        //TODO This is probably dependen on the order in which things are set
        function onActiveChanged(active) {
            if (!active) {
                categorySelector.currentIndex = 1
            } else {
                if (!group.small && !group.obsolete) {
                    categorySelector.currentIndex = 0
                }
            }
        }
        function onSmallChanged(small) {
            if (small) {
                categorySelector.currentIndex = 2
            } else {
                if (group.active && !group.obsolete) {
                    categorySelector.currentIndex = 0
                }
            }
        }
        function onObsoleteChanged(obsolete) {
            if (obsolete) {
                categorySelector.currentIndex = 3
            } else {
                if (group.active && !group.obsolete) {
                    categorySelector.currentIndex = 0
                }
            }
        }
    }

    Connections {
        target: editName
        function onClicked() {
            groupNameEdit.readOnly = false
            groupNameEdit.selectAll()
            groupNameEdit.focus = true
        }
    }

    Connections {
        target: groupNameEdit
        function onEditingFinished() {
            groupNameEdit.readOnly = true
            groupNameEdit.deselect()
            group.name = groupNameEdit.text
        }
    }
}
