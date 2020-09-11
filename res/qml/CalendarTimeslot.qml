import QtQuick 2.4

CalendarTimeslotForm {
    property var timeslot: dummysemesters.semesters[0].plans[0].weeks[0].days[0].timeslots[0]
    modulesRepeater.model: timeslot.modules
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.8999999761581421;height:480;width:640}
}
##^##*/

