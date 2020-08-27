import QtQuick 2.4

GroupEditorPopupForm {

    property alias group: groupEditor.myGroup
    id: groupEditor

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
