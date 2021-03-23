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
            if (Backend.schedulingState === Backend.Running) {
                Backend.stopPlanning()
            } else {
                Backend.startPlanning()
            }
        }
    }

    Connections {
        target: buildButtonMouseArea
        function onClicked() {
            if (Backend.schedulingState !== Backend.Running) {
                buildButtonMenu.popup()
            }
        }
    }

    Connections {
        target: scheduleFastMenuItem
        function onClicked() {
            Backend.startPlanning("legacy-fast")
        }
    }

    Connections {
        target: scheduleGoodMenuItem
        function onClicked() {
            Backend.startPlanning("legacy-good")
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

    buildButton.icon.source: {
        switch (Backend.schedulingState) {
        case Backend.Running:
            "qrc:/icons/material/stop-24px.svg"
            break
        case Backend.Failed:
            "qrc:/icons/material/play_arrow-24px.svg"
            break
        case Backend.Finished:
            "qrc:/icons/material/replay-24px.svg"
            break
        default:
            "qrc:/icons/material/play_arrow-24px.svg"
        }
    }
}
