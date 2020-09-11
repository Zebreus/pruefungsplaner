import QtQuick 2.4
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import org.pruefungsplaner.Backend 1.0

ResultViewForm {
    id: resultViewForm
    property alias daysPerWeek: resultViewForm.daysPerWeek
    property alias slotsPerDay: resultViewForm.slotsPerDay
    property alias weeks: resultViewForm.weeks

    anchors.fill: parent

    //weekLabelRepeater.model: dummysemesters.semesters[0].plans[0].weeks
    //dayLabelWeekRepeater.model: dummysemesters.semesters[0].plans[0].weeks
    //weeksRepeater.model: dummysemesters.semesters[0].plans[0].weeks
    //timeslotLabelRepeater.model: dummysemesters.semesters[0].plans[0].weeks[0].days[0].timeslots
    weekLabelRepeater.model: Backend.activePlan.weeks
    dayLabelWeekRepeater.model: Backend.activePlan.weeks
    weeksRepeater.model: Backend.activePlan.weeks
    timeslotLabelRepeater.model: Backend.activePlan.weeks[0].days[0].timeslots
}
