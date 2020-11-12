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
                group.small = false
                group.obsolete = false
                group.active = true
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
                group.obsolete = false
                group.small = true
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

    categorySelector {
        currentIndex: group.active ? 0 : group.small ? 2 : group.obsolete ? 3 : 1
    }

    Connections {
        target: perDaySelector
        function onValueModified() {
            group.examsPerDay = perDaySelector.value
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
