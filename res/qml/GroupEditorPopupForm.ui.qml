import QtQuick 2.4
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Popup {
    id: popup
    modal: false
    focus: true
    anchors.centerIn: parent
    padding: 0
    visible: true
    property alias categorySelector: categorySelector
    property alias perDaySelector: perDaySelector
    property alias daysRepeater: daysRepeater
    width: columnLayout.width
    height: columnLayout.height

    property alias editName: editName
    property alias groupNameEdit: groupNameEdit
    property int maxDaysPerWeek: 6
    property int maxSlotsPerDay: 6
    property var myGroup: dummysemesters.semesters[0].plans[0].groups[0]

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    DropShadow {
        anchors.fill: popupBackground
        visible: true
        horizontalOffset: 0
        verticalOffset: 0
        radius: 10
        samples: 5
        color: "black"
        source: popupBackground
    }

    Rectangle {
        id: popupBackground
        color: "white"
        width: popup.width
        height: popup.height
    }

    ColumnLayout {
        id: columnLayout

        RowLayout {
            id: titleRow
            Layout.alignment: Qt.AlignCenter
            TextInput {
                id: groupNameEdit
                text: myGroup.name
                cursorVisible: true
                readOnly: true
                font.pointSize: 20
                Layout.leftMargin: Layout.rightMargin + editName.width
                Layout.alignment: Qt.AlignCenter
                maximumLength: 50
            }

            ToolButton {
                id: editName
                padding: 0
                icon.name: "edit"
                icon.source: "qrc:/icons/material/create-24px.svg"
            }
        }

        //Grid will be filled by Repeater
        RowLayout {
            id: settingsRow

            Layout.fillWidth: true
            spacing: 10
            Layout.leftMargin: 10
            Layout.rightMargin: 10
            RowLayout {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Text {
                    id: perDayLabel
                    text: qsTr("Prüfungen pro Tag")
                }

                SpinBox {
                    id: perDaySelector
                    to: 6
                    from: 1
                    value: myGroup.examsPerDay
                }
            }

            ToolSeparator {
                Layout.fillWidth: true
                orientation: Qt.Vertical
                Layout.columnSpan: maxSlotsPerDay + 1
            }

            RowLayout {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillWidth: true

                Text {
                    //id: perDayLabel
                    text: qsTr("Kategorie")
                }

                ComboBox {
                    id: categorySelector
                    model: ["Aktiv", "Inaktiv", "Klein", "Veraltet"]
                }
            }
        }

        GridLayout {
            id: mainGrid
            Layout.topMargin: -7
            Layout.bottomMargin: 8
            Layout.margins: 5
            flow: GridLayout.LeftToRight
            Layout.fillWidth: true
            Layout.fillHeight: true
            columnSpacing: 5
            columns: maxSlotsPerDay + 1

            // Insert day names
            Repeater {
                id: daysRepeater
                model: dummysemesters.semesters[0].plans[0].weeks
                delegate: Repeater {
                    property int weekIndex: index
                    model: modelData.days
                    delegate: Label {
                        Layout.column: 0
                        Layout.row: 2 + index + weekIndex * (maxDaysPerWeek + 2)
                        text: modelData.name
                    }
                }
            }

            // Insert checkboxes
            Repeater {
                model: daysRepeater.model
                delegate: Repeater {
                    property int weekIndex: index
                    id: outerRepeater
                    model: modelData.days
                    delegate: Repeater {
                        property int rowIndex: index
                        model: modelData.timeslots
                        delegate: GroupCheckBox {
                            Layout.alignment: Qt.AlignCenter
                            Layout.fillWidth: true
                            id: groupCheckBox
                            Layout.row: 2 + rowIndex + weekIndex * (maxDaysPerWeek + 2)
                            Layout.column: index + 1
                            timeslot: modelData
                            group: myGroup
                            padding: 0
                        }
                    }
                }
            }

            //Insert dividers
            Repeater {
                model: daysRepeater.model
                delegate: ToolSeparator {
                    Layout.row: index * (maxDaysPerWeek + 2)
                    Layout.fillWidth: true
                    topPadding: 12
                    rightPadding: 10
                    leftPadding: 10
                    orientation: Qt.Horizontal
                    Layout.columnSpan: maxSlotsPerDay + 1
                }
            }

            //Insert hour names
            Repeater {
                model: daysRepeater.model
                delegate: Repeater {
                    property int weekIndex: index
                    model: modelData.days[0].timeslots
                    delegate: Label {
                        Layout.alignment: Qt.AlignCenter
                        Layout.fillWidth: true
                        Layout.column: 1 + index
                        Layout.row: 1 + weekIndex * (maxDaysPerWeek + 2)
                        text: modelData.name
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/

