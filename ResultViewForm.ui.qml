import QtQuick 2.4
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import Qt.labs.settings 1.0
import "dummydata"

Column {
    id: column

    //    ResultModel{
    //        id: resultModel
    //    }
    GridLayout {

        id: resultGrid
        anchors.left: parent.left
        anchors.right: parent.right

        columns: 7

        Repeater {
            model: 70
            delegate: DropArea {
                id: dropArea
                property string property0: "none.none"
                //Layout.fillWidth: true
                //Layout.fillHeight: true
                Layout.preferredHeight: dropColumn.implicitHeight
                Layout.preferredWidth: dropColumn.implicitWidth
                Layout.alignment: Qt.AlignLeft || Qt.alignTop
                //Layout.preferredWidth: childrenRect.width
                Rectangle {
                    color: "#10ffff00"
                    anchors.fill: parent
                    border.width: 2
                }
                ColumnLayout {
                    id: dropColumn
                    anchors.right: parent.right
                    anchors.left: parent.left
                    anchors.top: parent.top
                    DraggableExamDelegate {
                        text: "AAAAAA" + index
                    }
                    DraggableExamDelegate {
                        text: "BBBBBB" + index
                    }
                    DraggableExamDelegate {
                        text: "CCCCCC" + index
                    }
                }

                Connections {
                    target: testArea
                    onDropped: {
                        if (drag.source.parent != dropColumn) {
                            drag.source.x = 0
                            drag.source.y = 0
                            drag.source.parent = dropColumn
                            drop.acceptProposedAction()
                        } else {
                            drop.accept(Qt.IgnoreAction)
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
