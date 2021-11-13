import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12

Item{

    property alias text: tagText.text           // "Синоним" дочернего синонима для доступа извне

    id: tagAreaControl
    width: parent.width
    height: parent.height

    Rectangle{
        id: tagElement
        width: tagElementContent.width      // Изменение размера элемента в зависимости от размера содержимого
        height: 50
        opacity: 50 // Прозрачность
        color: "#33FFDD"
        radius: 5

        RowLayout{
            id: tagElementContent
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom

            Text {
                id: tagText
                text: qsTr("text")                  // Текст тега, который будет получаться от других элементов (н-р ввод из стрчоки)
                // Добавить еще свойства !!!
                // Шрифт, размер шрифта
            }
            Text {  // Визуальный элемент для удаления тега, при нажатии на эту область
                id: deleteTag
                text: "X"
            }

        }
    }
}
