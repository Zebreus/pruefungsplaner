import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ItemDelegate {
    id: delegate
    property var myModelData
    property bool showDetails: false
    property real realHeight: showDetails ? examDetails.implicitHeight : 0

    property alias mainLayout: mainLayout
    property alias addGroupButton: addGroupButton
    property alias addConstraintButton: addConstraintButton
    property alias groupPopup: groupPopup
    property alias constraintPopup: constraintPopup
    property alias activeCheckBox: activeCheckBox
    checkable: true
    verticalPadding: 5

    contentItem: ColumnLayout {
        id: mainLayout

        RowLayout {
            id: title
            Layout.fillWidth: true
            Layout.margins: 0
            RowLayout {
                id: leftOverview

                CheckBox {
                    id: activeCheckBox
                    display: AbstractButton.IconOnly
                    checkable: true
                    autoRepeat: false
                    autoExclusive: false
                    checked: delegate.myModelData.active
                    verticalPadding: 0
                }

                Label {
                    id: examName
                    text: delegate.myModelData.name
                }

                Label {
                    id: examNumber
                    text: delegate.myModelData.number
                }
            }

            Item {
                id: filler
                Layout.fillWidth: true
            }

            RowLayout {
                id: rightOverview

                Label {
                    text: delegate.myModelData.origin
                }
            }
        }

        ColumnLayout {
            id: examDetails
            Layout.preferredHeight: realHeight
            Layout.fillWidth: true
            clip: true

            GroupBox {
                id: groupBox
                Layout.fillWidth: true
                //: Heading for list of groups
                title: qsTr("Gruppen")
                spacing: 0

                Flow {
                    anchors.fill: parent
                    anchors.leftMargin: 2
                    anchors.rightMargin: 2
                    spacing: 10

                    Repeater {
                        model: delegate.myModelData.groups
                        id: groupList
                        delegate: RemovableLabel {
                            id: groupLabel
                            text: modelData.name
                            Connections {
                                target: groupLabel
                                function onRemoveClicked() {
                                    delegate.myModelData.removeGroup(modelData)
                                }
                            }
                        }
                    }
                }
            }

            Button {
                id: addGroupButton
                //: Text for button to manage groups
                text: qsTr("Gruppe hinzufügen", "add group")

                AddGroupPopup {
                    id: groupPopup
                    y: (parent.height / 3) * 2
                    x: parent.width / 2
                    visible: false
                }
            }

            GroupBox {
                id: constraintBox
                Layout.fillWidth: true
                //: Heading for list of constraints
                title: qsTr("Bedingungen")
                spacing: 0

                Flow {
                    anchors.fill: parent
                    anchors.leftMargin: 2
                    anchors.rightMargin: 2
                    spacing: 10

                    Repeater {
                        model: delegate.myModelData.constraints
                        id: constraintList
                        delegate: RemovableLabel {
                            id: constraintLabel
                            text: modelData.name
                            Connections {
                                target: constraintLabel
                                function onRemoveClicked() {
                                    delegate.myModelData.removeConstraint(
                                                modelData)
                                }
                            }
                        }
                    }
                }
            }
            Button {
                id: addConstraintButton
                //: Text for button to manage constraints
                text: qsTr("Bedingung hinzufügen", "add constraint")

                AddGroupPopup {
                    id: constraintPopup
                    y: (parent.height / 3) * 2
                    x: parent.width / 2
                    visible: false
                }
            }
        }
    }

    states: [
        State {
            name: "collapsed"
            when: !delegate.checked

            PropertyChanges {
                target: delegate
                showDetails: false
            }
        },
        State {
            name: "expanded"
            when: delegate.checked

            PropertyChanges {
                target: delegate
                showDetails: true
            }
        }
    ]
}
