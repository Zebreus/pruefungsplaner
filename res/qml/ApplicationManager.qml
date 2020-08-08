import QtQuick 2.4

ApplicationManagerForm {
    anchors.fill: parent

    titleBar{
        onPlanClicked: stackLayout.currentIndex = 0;
        onCalendarClicked: stackLayout.currentIndex = 1;
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
