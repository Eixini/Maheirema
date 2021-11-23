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

    property alias inputText: enterIngredientsLine.text
    property alias modelId: tagsModel

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

    ListModel{
        id: tagsModel
    }

    ColumnLayout{
        id: headLayout
        anchors.fill: parent

        // Field for enter Ingredients
        TextField{
            id: enterIngredientsLine
            height: 50
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter     // Выравнивание по верхнему центру
            Layout.fillWidth: true                              // Заполнение всей ширины
            Layout.margins: 15                                  // Установка отступов
            placeholderText: qsTr("Enter the ingredient (example \"potato\")")      // Текст заполнитель

            onAccepted:{
                    if(text != "")      // Если строка пуста, то создание тега не происходит
                       tagsModel.append({"tag": text});
                    text = ""           // Очистка поля ввода после отправки тега в поле тегов
                }



        }

        /* -------------------------------------- ЗДЕСЬ БУДЕТ ВИДЖЕТ С ВЫБРАННЫМИ ИНГРЕДИЕНТАМИ -------------------------------------------*/

        ScrollView {

            id: scrollForTagsField
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            Layout.margins: 10
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: windowMain.width
            clip: true
            Flow {

                width: scrollForTagsField.width
                id: tagarea
                spacing: 7
                padding: 4

                Repeater{
                    id: tagRepeater

                    delegate:  Tag {
                            tag: model.tag
                            onDeleteTag: tagsModel.remove(index)
                        }

                    model: tagsModel

                }

            }
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

                onClicked: {
                    // Запрос в БД

                    // ...
                    // Отладочный код

                    for(var i = 0; i < tagsModel.count ; i++)
                    {
                        console.log(tagsModel.get(i).tag);
                    }
                }
            }

            Button{
                id: exitButton
                text: qsTr("Exit")
                width: 70
                height: 40

                onClicked: {
                    Qt.callLater(Qt.quit);
                }

            }
        }
    }

}
