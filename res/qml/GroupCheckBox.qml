import QtQuick 2.4

GroupCheckBoxForm {
    property var group
    property var timeslot
    checked: timeslot.containsActiveGroup(group)
    id: groupCheckBox
    Connections {
        target: groupCheckBox
        function onCheckedChanged() {
            if (groupCheckBox.checked) {
                timeslot.addActiveGroup(group)
            } else {
                timeslot.removeActiveGroup(group)
            }
        }
    }
}
