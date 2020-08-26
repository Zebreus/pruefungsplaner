import QtQuick 2.4
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.14

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
                    text: qsTr("")
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
                                onRemoveClicked: delegate.myModelData.removeGroup(
                                                     modelData)
                            }
                        }
                    }
                }
            }

            Button {
                id: addGroupButton
                text: qsTr("Gruppe hinzufügen")

                AddGroupPopup {
                    id: groupPopup
                    y: (parent.height / 3) * 2
                    x: parent.width / 2
                    anchors.centerIn: none
                    visible: false
                }
            }

            GroupBox {
                id: constraintBox
                Layout.fillWidth: true
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
                                onRemoveClicked: delegate.myModelData.removeConstraint(
                                                     modelData)
                            }
                        }
                    }
                }
            }
            Button {
                id: addConstraintButton
                text: qsTr("Bedingung hinzufügen")

                AddGroupPopup {
                    id: constraintPopup
                    y: (parent.height / 3) * 2
                    x: parent.width / 2
                    anchors.centerIn: none
                    visible: false
                }
            }
        }
    }

    Connections {
        target: activeCheckBox
        onCheckedChanged: delegate.myModelData.active = activeCheckBox.checked
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
