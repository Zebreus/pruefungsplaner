import QtQuick 2.4
import QtQuick.Controls 2.2
import org.pruefungsplaner.Backend 1.0

TitleBarForm {

    signal planClicked
    signal calendarClicked

    semesterSelector {
        model: Backend.semesters
    }

    planSelector {
        model: Backend.activeSemester.plans
    }

    Connections {
        target: semesterSelector
        function onActivated() {
            if (index != -1) {
                Backend.activeSemester = Backend.semesters[index]
                Backend.activePlan = Backend.activeSemester.plans[0]
            }
        }
    }

    Connections {
        target: planSelector
        function onActivated() {
            if (index != -1) {
                Backend.activePlan = Backend.activeSemester.plans[index]
            }
        }
    }

    Behavior on buildProgress.value {
        NumberAnimation {
            id: moveAnim
            duration: 350
            easing.type: Easing.InOutQuad
        }
    }

    Connections {
        target: buildButton
        function onClicked() {
            Backend.startPlanning()
        }
    }

    Connections {
        target: overviewButton
        function onClicked() {
            planClicked()
        }
    }

    Connections {
        target: resultButton
        function onClicked() {
            calendarClicked()
        }
    }

    buildProgress.value: Backend.progress
}
