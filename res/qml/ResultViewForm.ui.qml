import QtQuick 2.4
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import Qt.labs.settings 1.0
import org.pruefungsplaner.Backend 1.0
import "dummydata"

Column {
    anchors.fill: parent
    Layout.fillHeight: true
    Layout.fillWidth: true
    Flickable {
        anchors.fill: parent
        flickableDirection: Flickable.VerticalFlick
        contentHeight: groupsLayout.implicitHeight
        boundsBehavior: Flickable.DragOverBounds
        ColumnLayout {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillWidth: true
            id: columnLayout
            anchors.fill: parent
            Repeater {
                id: weeksRepeater
                model: Backend.activePlan.weeks
                delegate: ColumnLayout {
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    id: columnLayout2
                    Layout.fillWidth: true

                    Label {
                        text: modelData.name
                    }

                    ColumnLayout {
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        id: columnLayout25
                        Layout.leftMargin: 10
                        Layout.fillWidth: true
                        Repeater {
                            id: weeksRepeater2
                            model: modelData.days
                            delegate: ColumnLayout {
                                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                                id: columnLayout3
                                Layout.fillWidth: true

                                Label {
                                    text: modelData.name
                                }

                                ColumnLayout {
                                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                                    id: columnLayout35
                                    Layout.fillWidth: true
                                    Layout.leftMargin: 10

                                    Repeater {
                                        id: weeksRepeater3
                                        model: modelData.timeslots
                                        delegate: ColumnLayout {
                                            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                                            id: columnLayout45
                                            Layout.fillWidth: true

                                            Label {
                                                text: modelData.name
                                                Layout.fillWidth: true
                                            }
                                            RowLayout {
                                                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                                                id: rowLayout45
                                                Layout.fillWidth: true
                                                Repeater {
                                                    id: weeksRepeater4
                                                    model: modelData.modules
                                                    delegate: ResultViewModuleItem {
                                                        dataModel: modelData
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
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
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

