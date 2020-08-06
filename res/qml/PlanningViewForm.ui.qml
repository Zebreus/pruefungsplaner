import QtQuick 2.4
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3

import org.pruefungsplaner.Backend 1.0

SplitView {
    id: mainSplitView
    property alias newGroupMouseArea: newGroupMouseArea
    property alias groupList: groupList
    property alias newConstraintMouseArea: newConstraintMouseArea
    property alias constraintList: constraintList
    Layout.minimumWidth: 100
    Layout.maximumWidth: 500
    orientation: Qt.Horizontal
    anchors.fill: parent
    Layout.fillHeight: true
    Layout.fillWidth: true

    Flickable {
        SplitView.minimumWidth: 200
        SplitView.preferredWidth: 200
        flickableDirection: Flickable.VerticalFlick
        contentHeight: groupsLayout.implicitHeight
        boundsBehavior: Flickable.DragOverBounds

        ColumnLayout {
            id: groupsLayout
            anchors.fill: parent

            GroupBox {
                padding: 5
                Layout.leftMargin: 6
                Layout.rightMargin: 6
                Layout.topMargin: 5
                Layout.alignment: Qt.AlignTop
                Layout.fillWidth: true
                Layout.minimumHeight: 200
                spacing: 0
                title: qsTr("Gruppen")
                ColumnLayout {
                    id: groupList
                    anchors.right: parent.right
                    anchors.left: parent.left

                    Repeater {
                        model: Backend.activePlan.groups
                        delegate: RowLayout {
                            Layout.fillWidth: true

                            Label {
                                text: modelData.name
                                Layout.fillWidth: true
                                MouseArea {
                                    id: groupMouseArea
                                    anchors.fill: parent
                                }
                            }

                            CheckBox {
                                id: groupCheckBox
                                display: AbstractButton.IconOnly
                                verticalPadding: 0
                                checked: modelData.selected
                                Connections {
                                    target: groupCheckBox
                                    onCheckedChanged: modelData.selected = groupCheckBox.checked
                                }
                            }

                            Popup {
                                id: groupEditorPopup
                                dim: true
                                modal: true
                                focus: true
                                anchors.centerIn: Overlay.overlay
                                closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                                AvailabilityEditor {
                                    id: availabilityEditorPopup
                                    group: modelData
                                }
                            }

                            Connections {
                                target: groupMouseArea
                                onClicked: groupEditorPopup.open()
                            }
                        }
                    }

                    MouseArea {
                        id: newGroupMouseArea
                        Layout.fillWidth: true
                        implicitHeight: children[0].implicitHeight

                        RowLayout {
                            anchors.fill: parent

                            Label {
                                text: "Neue Gruppe"
                                Layout.fillWidth: true
                            }

                            Image {
                                Layout.leftMargin: 9
                                Layout.rightMargin: 9
                                source: "qrc:/icons/material/add-24px.svg"
                            }
                        }
                    }
                }
            }

            GroupBox {
                id: groupBox
                padding: 5
                Layout.leftMargin: 6
                Layout.rightMargin: 6
                Layout.topMargin: 5
                Layout.alignment: Qt.AlignTop
                Layout.fillWidth: true
                Layout.minimumHeight: 200
                spacing: 0

                title: qsTr("Bedingungen")
                ColumnLayout {
                    id: constraintList
                    anchors.right: parent.right
                    anchors.left: parent.left

                    Repeater {

                        model: Backend.activePlan.constraints
                        Layout.fillWidth: true
                        delegate: RowLayout {
                            Layout.fillWidth: true

                            Label {
                                text: modelData.name
                                Layout.fillWidth: true
                                MouseArea {
                                    id: constraintMouseArea
                                    anchors.fill: parent
                                }
                            }

                            CheckBox {
                                id: constraintCheckBox
                                display: AbstractButton.IconOnly
                                verticalPadding: 0
                                checked: modelData.selected
                                Connections {
                                    target: constraintCheckBox
                                    onCheckedChanged: modelData.selected
                                                      = constraintCheckBox.checked
                                }
                            }

                            Popup {
                                id: constraintEditorPopup
                                dim: true
                                modal: true
                                focus: true
                                anchors.centerIn: Overlay.overlay
                                closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                                AvailabilityEditor {
                                    id: constraintAvailabilityEditorPopup
                                    group: modelData
                                }
                            }

                            Connections {
                                target: constraintMouseArea
                                onClicked: constraintEditorPopup.open()
                            }
                        }
                    }
                    MouseArea {
                        id: newConstraintMouseArea
                        Layout.fillWidth: true
                        implicitHeight: children[0].implicitHeight

                        RowLayout {
                            anchors.fill: parent

                            Label {
                                text: "Neue Bedingung"
                                Layout.fillWidth: true
                            }

                            Image {
                                Layout.leftMargin: 9
                                Layout.rightMargin: 9
                                source: "qrc:/icons/material/add-24px.svg"
                            }
                        }
                    }
                }
            }

            Item {
                Layout.fillHeight: true
            }
        }
    }

    RowLayout {
        id: rowLayout
        SplitView.minimumWidth: 400
        SplitView.fillWidth: true

        Flickable {
            id: flickable
            flickableDirection: Flickable.VerticalFlick
            Layout.fillWidth: true
            Layout.fillHeight: true
            contentHeight: root.implicitHeight
            boundsBehavior: Flickable.DragOverBounds

            Pane {
                id: root
                anchors.fill: parent

                Column {
                    id: column
                    anchors.right: parent.right
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.fill: parent
                    Layout.fillWidth: true

                    //                    BackEnd {
                    //                        id: modelbackend
                    //                    }
                    Repeater {
                        id: examList
                        model: Backend.activePlan.modules
                        anchors.fill: parent
                        //                        delegate: Label {
                        //                            //width: 60
                        //                            //height: 30
                        //                            text: model.name
                        //                        }
                        //                        delegate: Rectangle {
                        //                            width: 100
                        //                            height: 100
                        //                            color: "#f70000"
                        //                            radius: 2
                        //                            border.width: 2
                        //                            border.color: "#1dff4f"
                        //                        }
                        //                        delegate: Button {
                        //                            text: modelData.name
                        //                            onClicked: modelData.name = "test"
                        //                        }
                        delegate: ExamListItem {
                            dataModel: modelData
                        }
                    }
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

