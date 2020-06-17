import QtQuick 2.4
import "dummydata"
import QtQuick.Controls 2.2
import org.pruefungsplaner.Backend 1.0

TitleBarForm {

    signal planClicked()
    signal calendarClicked()

    SemesterModel {
        id: semesterModel
    }

    semesterSelector{
        model: Backend.semesters
    }

    planSelector{
        model: Backend.activeSemester.plans
    }

    Connections {
        target: semesterSelector
        onActivated: {
            if(index != -1){
                Backend.activeSemester = Backend.semesters[index];
                Backend.activePlan = Backend.activeSemester.plans[0];
            }
        }
    }

    Connections {
        target: planSelector
        onActivated: {
            if(index != -1){
                Backend.activePlan = Backend.activeSemester.plans[index];
            }
        }
    }

    Connections {
        target: buildButton
        onClicked: Backend.startPlanning()
    }

    Connections {
        target: overviewButton
        onClicked: planClicked()
    }

    Connections {
        target: resultButton
        onClicked: calendarClicked()
    }


}
