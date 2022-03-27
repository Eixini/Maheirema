import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import RecipeRequestModule 1.0      // Модуль из C++
import RecipeModel

Page{
    id: ingredientEntryWindow
    title: "Mahεirεma";

    property alias inputText: enterIngredientsLine.text
    property alias modelId: tagsModel
    property RecipeModel recipeModel

    Image {
        id: backgroundImage
        source: "qrc:/maheirema_resource/image/image/mh_background.png"
        width: 1920
        height: 1080
        visible: true
        anchors.fill: parent

    } // End of BACKGROUND image block

    ListModel{
        id: tagsModel
    }

    // Field for enter Ingredients
    TextField{
        id: enterIngredientsLine
        height: 30  // Со временем сделать высоту исходя из размера шрифта в настройках + некоторое значение
        width: parent.width - 40
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 15
        placeholderText: qsTr("Enter the ingredient (example \"potato\")")      // Текст заполнитель

        onAccepted:{
                if(text != "")      // Если строка пуста, то создание тега не происходит
                   tagsModel.append({"tag": text});
                text = ""           // Очистка поля ввода после отправки тега в поле тегов
            }

    } // End of the TextField block for entering ingredients

    ScrollView {

        id: scrollForTagsField
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        anchors.top: enterIngredientsLine.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: requestButton.top
        anchors.margins: 15

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

            } // End of the Repeater block

        } // End of Flow block

    // End of the ScrollView block to scroll the tag field
    }

    /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */


        Button{
            id: requestButton
            text: qsTr("Request a recipe")
            width: 120
            height: 40
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.leftMargin: 30
            anchors.bottomMargin: 10

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
                    for(var i = 0; i < tagsModel.count ; i++){
                        tagsTextList[i] = tagsModel.get(i).tag;
                    }
                    recipeModel.setIntroducedIngredients(tagsTextList);
                    console.log("Number of Ingredients Introduced (in QML):" + tagsTextList.length);       // В целях отладки

//                    avaibleIngredientsList.obtainingRecipesForAvailableIngredients(tagsTextList)
//                    resultRecipeWindow.recipeModel.setIntroducedIngredients(tagsTextList);

                    let suitableDataSize = 0;
                    suitableDataSize = avaibleIngredientsList.numberEligibleRecipes(tagsTextList);

                    console.log("IN ON CLICK HANDLER: " + suitableDataSize);

                    // If the number of matching recipes is not equal to 0,
                    // then a window with the results is opened
                    if(suitableDataSize !== 0){
                        stackView.push(resultRecipePageComponent.createObject(parent, {"ingredientsForModel": tagsTextList}));
                        console.log(tagsTextList);
                        windowMain.statusText =
                                String("Found according to your request " + suitableDataSize + " recipes! ");
                    }
                    else {
                        windowMain.statusText =
                                String("Found according to your request " + suitableDataSize + " recipes! ");
                }

                } // End of code block "If there are ingredients entered"

            } // End of Button click (RecipeRequest) handler code block

        } // End of Recipe Request Button Code Block

        Button{
            id: exitButton
            text: qsTr("Exit")
            width: 70
            height: 40
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.rightMargin: 30
            anchors.bottomMargin: 10

            onClicked: { Qt.callLater(Qt.quit); }

        } // // End of "Exit Button" Code Block



// End Page "ingredientEntryWindow"
}
