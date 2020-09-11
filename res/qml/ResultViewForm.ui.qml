import QtQuick 2.4
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import Qt.labs.settings 1.0

Item {
    width: 640
    height: 480
    property alias weeksRepeater: weeksRepeater
    property alias timeslotLabelRepeater: timeslotLabelRepeater
    property alias dayLabelWeekRepeater: dayLabelWeekRepeater
    property alias weekLabelRepeater: weekLabelRepeater

    property var daysPerWeek: 6
    property var weeks: 3
    property var slotsPerDay: 6

    Flickable {
        anchors.fill: parent
        flickableDirection: Flickable.HorizontalFlick
        contentWidth: mainGrid.implicitWidth
        boundsBehavior: Flickable.DragOverBounds
        ScrollBar.horizontal: ScrollBar {
            interactive: true
        }

        Rectangle {
            anchors.fill: mainGrid
            color: "black"
        }

        GridLayout {
            id: mainGrid
            height: parent.height
            width: parent.parent.width > implicitWidth ? parent.parent.width : implicitWidth
            columnSpacing: 1
            rowSpacing: 1

            Rectangle {
                Layout.row: 0
                Layout.column: 0
                Layout.rowSpan: 2
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: "white"
            }

            //Fill day labels
            Repeater {
                id: weekLabelRepeater
                model: dummysemesters.semesters[0].plans[0].weeks
                delegate: Label {
                    Layout.row: 0
                    Layout.column: 1 + (index * daysPerWeek)
                    Layout.columnSpan: daysPerWeek
                    Layout.fillWidth: true
                    Layout.preferredHeight: implicitHeight
                    padding: 3
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: modelData.name
                    background: Rectangle {
                        color: "white"
                    }
                }
            }

            //Fill day labels
            Repeater {
                id: dayLabelWeekRepeater
                model: dummysemesters.semesters[0].plans[0].weeks
                delegate: Repeater {
                    property int weekIndex: index
                    id: dayLabelDayRepeater
                    model: modelData.days
                    delegate: Label {
                        Layout.row: 1
                        Layout.column: 1 + (weekIndex * daysPerWeek + index)
                        Layout.fillWidth: true
                        padding: 3
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        text: modelData.name
                        background: Rectangle {
                            color: "white"
                        }
                    }
                }
            }

            //Fill timeslots
            Repeater {
                id: timeslotLabelRepeater
                model: dummysemesters.semesters[0].plans[0].weeks[0].days[0].timeslots
                delegate: Label {
                    Layout.row: index + 2
                    Layout.column: 0
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    padding: 3
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: modelData.name
                    background: Rectangle {
                        color: "white"
                    }
                }
            }

            //Fill modules
            Repeater {
                id: weeksRepeater
                model: dummysemesters.semesters[0].plans[0].weeks
                delegate: Repeater {
                    property int weekIndex: index
                    id: daysRepeater
                    model: modelData.days
                    delegate: Repeater {
                        property int dayIndex: index
                        id: timeslotsRepeater
                        model: modelData.timeslots
                        delegate: CalendarTimeslot {
                            //Layout.row: index * 2
                            //Layout.column: (weekIndex * daysPerWeek + dayIndex) * 2
                            Layout.row: index + 2
                            Layout.column: (weekIndex * daysPerWeek + dayIndex) + 1
                            timeslot: modelData
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            Rectangle {
                                anchors.fill: parent
                                color: "white"
                                z: -1
                            }

                            //text: "hi"
                        }
                    }
                }
            }
        }
    }

    //    ResultModel{
    //        id: resultModel
    //    }
    //    GridLayout {

    //        id: resultGrid
    //        anchors.left: parent.left
    //        anchors.right: parent.right

    //        columns: 7

    //        Repeater {
    //            model: 70
    //            delegate: DropArea {
    //                id: dropArea
    //                property string property0: "none.none"
    //                //Layout.fillWidth: true
    //                //Layout.fillHeight: true
    //                Layout.preferredHeight: dropColumn.implicitHeight
    //                Layout.preferredWidth: dropColumn.implicitWidth
    //                Layout.alignment: Qt.AlignLeft || Qt.alignTop
    //                //Layout.preferredWidth: childrenRect.width
    //                Rectangle {
    //                    color: "#10ffff00"
    //                    anchors.fill: parent
    //                    border.width: 2
    //                }
    //                ColumnLayout {
    //                    id: dropColumn
    //                    anchors.right: parent.right
    //                    anchors.left: parent.left
    //                    anchors.top: parent.top
    //                    DraggableExamDelegate {
    //                        text: "AAAAAA" + index
    //                    }
    //                    DraggableExamDelegate {
    //                        text: "BBBBBB" + index
    //                    }
    //                    DraggableExamDelegate {
    //                        text: "CCCCCC" + index
    //                    }
    //                }

    //                Connections {
    //                    target: testArea
    //                    onDropped: {
    //                        if (drag.source.parent != dropColumn) {
    //                            drag.source.x = 0
    //                            drag.source.y = 0
    //                            drag.source.parent = dropColumn
    //                            drop.acceptProposedAction()
    //                        } else {
    //                            drop.accept(Qt.IgnoreAction)
    //                        }
    //                    }
    //                }
    //            }
    //        }
    //    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.25}
}
##^##*/

