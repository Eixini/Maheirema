import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12

Rectangle {
    property alias tag: tagText.text

    signal deleteTag()

    id: tagElement
    width: contentRow.width
    height: contentRow.height
    radius: 5
    color: "#33FFDD"

    Row{
        id: contentRow
        spacing: 4

        Label {
            id: tagText
            anchors.verticalCenter: parent.verticalCenter

        // End of block with tag text
        }
        Label {
            text: " ✘ "

            MouseArea {
                    anchors.fill: parent
                    onClicked: deleteTag()
                    anchors.verticalCenter: parent.verticalCenter
                }
        // End of block with end character for tag
        }

    // End of text builder block and closing character for tag
    }

}