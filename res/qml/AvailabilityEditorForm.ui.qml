import QtQuick 2.4
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3

import org.pruefungsplaner.Backend 1.0

ColumnLayout {
    property alias editName: editName
    property alias groupNameEdit: groupNameEdit
    property int maxDaysPerWeek: 6
    property int maxSlotsPerDay: 6
    property var myGroup

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
            icon.source: "res/icons/material/create-24px.svg"
        }
    }

    //Grid will be filled by Repeater
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
            model: Backend.activePlan.weeks
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
            model: Backend.activePlan.weeks
            delegate: Repeater {
                property int weekIndex: index
                id: outerRepeater
                model: modelData.days
                delegate: Repeater {
                    property int rowIndex: index
                    model: modelData.timeslots
                    delegate: CheckBox {
                        id: groupCheckBox
                        Layout.row: 2 + rowIndex + weekIndex * (maxDaysPerWeek + 2)
                        Layout.column: index + 1
                        checked: modelData.containsActiveGroup(myGroup)
                        display: AbstractButton.IconOnly
                        padding: 0
                        Connections {
                            target: groupCheckBox
                            onCheckedChanged: {
                                if (groupCheckBox.checked) {
                                    modelData.addActiveGroup(myGroup)
                                } else {
                                    modelData.removeActiveGroup(myGroup)
                                }
                            }
                        }
                    }
                }
            }
        }

        //Insert dividers
        Repeater {
            model: Backend.activePlan.weeks
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
            model: Backend.activePlan.weeks
            delegate: Repeater {
                property int weekIndex: index
                model: modelData.days[0].timeslots
                delegate: Label {
                    Layout.column: 1 + index
                    Layout.row: 1 + weekIndex * (maxDaysPerWeek + 2)
                    text: modelData.name
                }
            }
        }
    }
}
