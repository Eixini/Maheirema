import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12

import "tagCreation.js" as TagCreationScript

Rectangle {
    property alias text: tagText.text

    id: tagElement
    width: tagText.width + tagElementLayout.spacing + deleteTag.width
    height: tagText.height
    radius: 5
    opacity: 75
    color: "#33FFDD"

    RowLayout{
        id: tagElementLayout
        spacing: 3

        Label {
            id: tagText
            text: qsTr()
        }
        Label {
            id: deleteTag
            width: tagText.width
            height: tagText.height
            text: " X "

            MouseArea {
                    anchors.fill: parent
                    onClicked: {

                        // При нажатии на область, произойдет удаление тега
                        tagElement.destroy();
                    }
                }
        }

    }

}
