import QtQuick 2.4
import QtQml.Models 2.3

import org.pruefungsplaner.Backend 1.0

AddGroupPopupForm {
    id: popup
    //Need to listen on active Groups changed and copy change
    property alias activeGroups: popup.activeGroups
    property var groups
    activeGroups: Backend.activePlan.modules[0].groups
    groups: Backend.activePlan.groups

    Connections{
        target: filterTextField
        function onTextChanged() {
            popup.visibleGroups = groups.filter(modelData => modelData.name.includes(filterTextField.text))
        }
    }

    Connections{
        target: popup
        onOpened: {
            popup.filterTextField.text = "";
            popup.filterTextField.focus = true;
            popup.visibleGroups = groups;
        }
    }

    Behavior on height {
        NumberAnimation {
            duration: 100
            easing.type: Easing.Linear
        }
    }

    Behavior on width {
        NumberAnimation {
            duration: 100
            easing.type: Easing.Linear
        }
    }
}
