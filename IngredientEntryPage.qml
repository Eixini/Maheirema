import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import RecipeRequestModule 1.0      // Модуль из C++

Page{
    id: ingredientEntryWindow
    title: "Mahεirεma";

    property alias inputText: enterIngredientsLine.text
    property alias modelId: tagsModel

    Image {
        id: backgroundImage
        source: "qrc:/maheirema_resource/image/image/mh_background.png"
        width: 1920
        height: 1080
        visible: true
        anchors.fill: parent

    // End of BACKGROUND image block
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
        // End of the TextField block for entering ingredients
        }

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
                // End of the Repeater block
                }
            // End of Flow block
            }
        // End of the ScrollView block to scroll the tag field
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

                    let tagsTextList = new Array()           // Массив текста тегов для отправки в C++ функцию

                    if(tagsModel.count === 0)
                    {
                        // Если нет тегов, то показываем соответсвующее сообщение
                        console.log("You have not entered any ingredient!");
                        windowMain.statusText = String("You have not entered any ingredient!");
                    }
                    else
                    {
                        for(var i = 0; i < tagsModel.count ; i++)
                        {
                            //console.log(tagsModel.get(i).tag);
                            tagsTextList[i] = tagsModel.get(i).tag;
                        }
                        console.log("Number of Ingredients Introduced (in QML):" + tagsTextList.length);       // В целях отладки

                        avaibleIngredientsList.obtainingRecipesForAvailableIngredients(tagsTextList)

                        console.log("IN ON CLICK HANDLER: " + avaibleIngredientsList.getListSuitableRecipesSize());

                        // If the number of matching recipes is not equal to 0,
                        // then a window with the results is opened
                        if(avaibleIngredientsList.getListSuitableRecipesSize() !== 0){
                            stackView.push(resultRecipePage);

                            windowMain.statusText =
                                    String("Found according to your request "
                                           + avaibleIngredientsList.getListSuitableRecipesSize()
                                           + " recipes! ");
                        }
                        else {
                            windowMain.statusText =
                                    String("Found according to your request "
                                           + avaibleIngredientsList.getListSuitableRecipesSize()
                                           + " recipes! ");
                    }

                    } // End of code block "If there are ingredients entered"

                } // End of Button click (RecipeRequest) handler code block

            } // End of Recipe Request Button Code Block

            Button{
                id: exitButton
                text: qsTr("Exit")
                width: 70
                height: 40

                onClicked: { Qt.callLater(Qt.quit); }

            } // // End of "Exit Button" Code Block

        } // End of "Layout for Buttons" Code Block

    // End "ColumnLayout for headLayout" code block
    }

// End Page "ingredientEntryWindow"
}
