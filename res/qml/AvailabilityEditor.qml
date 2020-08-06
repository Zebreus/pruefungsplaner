import QtQuick 2.4

AvailabilityEditorForm {
    anchors.fill: parent

    property alias group: availabilityEditorForm.myGroup
    id: availabilityEditorForm

    Connections{
        target: editName
        onClicked: {
            groupNameEdit.readOnly = false;
            groupNameEdit.selectAll();
            groupNameEdit.focus = true;
        }
    }

    Connections{
        target: groupNameEdit
        onEditingFinished:{
            groupNameEdit.readOnly = true;
            groupNameEdit.deselect();
            group.name = groupNameEdit.text;
        }
    }
}
