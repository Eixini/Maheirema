import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12

import "tagCreation.js" as TagCreationScript

/*
   Заметки разработки:
   -подключить к кнопкам действия (сигна-слот);
   - задать дейтсвие при нажатии Enter, когда активен виджет строчки ввода (содержимое будет добавляться в поле тегов);
*/

Window {

    property alias inputText: enterIngredientsLine.text

    id: windowMain
    width: 640
    //height: 480
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
            height: 50
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter     // Выравнивание по верхнему центру
            Layout.fillWidth: true                              // Заполнение всей ширины
            Layout.margins: 15                                  // Установка отступов
            placeholderText: qsTr("Enter the ingredient (example \"potato\")")      // Текст заполнитель

            Connections{
                target: enterIngredientsLine

                property var inputText: enterIngredientsLine.text

                function onAccepted(){
                    if(enterIngredientsLine.text != "")                 // Если строка пуста, то создание тега не происходит
                        TagCreationScript.createTagObject(inputText);
                    enterIngredientsLine.text = "";
                }

            }



        }


        /* -------------------------------------- ЗДЕСЬ БУДЕТ ВИДЖЕТ С ВЫБРАННЫМИ ИНГРЕДИЕНТАМИ -------------------------------------------*/

//        ScrollView{
//            id: scrollForTagsField
//            ScrollBar.vertical.policy: ScrollBar.AlwaysOn
//            ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
//            Layout.alignment: Qt.AlignTop | Qt.AlignVCenter
//            Layout.margins: 10
//            Layout.fillWidth: true
//            height: windowMain.height - enterIngredientsLine.height - buttonsLayout.height;
//            //clip: true



//        }

        Flow{
           id: tagarea
           spacing: 7
           Layout.alignment: Qt.AlignTop | Qt.AlignVCenter
           Layout.margins: 10
           Layout.fillWidth: true
           height: windowMain.height - enterIngredientsLine.height - buttonsLayout.height;

           ScrollBar.vertical: ScrollBar {
               parent: tagarea.parent
               policy: ScrollBar.AsNeeded
               anchors.top: tagarea.top
               anchors.right: tagarea.right
               anchors.bottom: tagarea.bottom
           }

           Component.onCompleted: TagCreationScript.createTagObject

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
            }

            Button{
                id: exitButton
                text: qsTr("Exit")
                width: 70
                height: 40

            }
        }
    }

}

/*      ЗАМЕТКИ ПО ИСПОЛЬЗУЕМЫМ РЕМУРСАМ (Документы, статьи, видео и т.д

  https://doc.qt.io/qt-5/qtqml-javascript-dynamicobjectcreation.html    - создание динамических объектов с помощью JavaScript
  https://doc.qt.io/qt-5/qtqml-syntax-signals.html#connecting-signals-to-methods-and-signals - Система событий сигналов и обработчиков


*/
