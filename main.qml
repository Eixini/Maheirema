import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12

/*
   Заметки разработки:
   -подключить к кнопкам действия (сигна-слот);
   - задать дейтсвие при нажатии Enter, когда активен виджет строчки ввода (содержимое будет добавляться в поле тегов);
*/

Window {

    id: windowMain
    width: 640
    height: 480
    visible: true
    title: qsTr("Mahεirεma");

    Image {
        id: backgroundImage
        source: "qrc:/maheirema_resource/image/image/mh_background.png"
        width: 1920
        height: 1080
        visible: true
        anchors.fill: parent

    }

    ColumnLayout{
        id: headLayout
        width: windowMain.width
        height: windowMain.height

        // Field for enter Ingredients
        TextField{
            id: enterIngredientsLine
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter     // Выравнивание по верхнему центру
            Layout.fillWidth: true                              // Заполнение всей ширины
            Layout.margins: 15                                  // Установка отступов
            placeholderText: qsTr("Enter the ingredient (example \"potato\")")      // Текст заполнитель

        }

        /* -------------------------------------- ЗДЕСЬ БУДЕТ ВИДЖЕТ С ВЫБРАННЫМИ ИНГРЕДИЕНТАМИ -------------------------------------------*/
       TagArea{
           id: tagarea
           Layout.margins: 15
           anchors.top: enterIngredientsLine.bottom

       }
        /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

        RowLayout{
            id: buttonsLayout
            width: headLayout.width
            height: 40
            Layout.alignment: Qt.AlignBottom | Qt.AlignHCenter
            Layout.margins: 15

            Button{
                id: requestButton
                text: qsTr("Request a recipe")
                width: 70
                height: 40
                Layout.alignment: Qt.AlignLeft
            }

            Button{
                id: exitButton
                text: qsTr("Exit")
                width: 70
                height: 40
                Layout.alignment: Qt.AlignRight
            }
        }
    }

}
