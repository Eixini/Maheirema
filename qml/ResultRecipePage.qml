import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import RecipeModel

Page{
    property RecipeModel model
    property alias ingredientsForModel: filteredModel.ingredients

    id: resultRecipeWindow
    title: "Mahεirεma"

    RecipeFilterProxyModel {
        id: filteredModel
        model: resultRecipeWindow.model
        ingredients: []

        onIngredientsChanged: {
            console.log("In QML ResultRecipe Page, input data:" + filteredModel.ingredients);
            filteredModel.updateRecipeData(filteredModel.ingredients);
        }

    }

    Image {
        id: backgroundImage
        source: "qrc:/maheirema_resource/image/image/mh_background.png"
        width: 1920
        height: 1080
        visible: true
        anchors.fill: parent

    // End of BACKGROUND image block
    }

    ListView{
        id: resultRecipesList
        width: 200
        anchors.top: parent.top
        anchors.bottom: toIngredientEntryWindowButton.top
        anchors.left: parent.left
        anchors.margins: 15
        spacing: 5
        clip: true


        header: Rectangle{
            width: parent.width
            height: 50
            color: '#00A287'
            anchors.bottomMargin: 10
            Text {
                id: viewHeaderText
                anchors.centerIn: parent
                text: qsTr("Найденный рецепты")
            }
        } // End of window HEADER code block

        model: filteredModel
        delegate: ItemDelegate {

            id: recipeElement
            height: 30          // !!! Со временем будет РазмерТекста + некоторое значение
            width: parent.width
            background: Rectangle {
                color: '#33FFDD'
                radius: 5
            } // End of background for ItemDelegate

            contentItem: Text {
                rightPadding: recipeElement.spacing
                text: model.recipeName
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            } // End of TEXT for "ItemDelegate"

            onClicked: {
                recipeDisplay.text = avaibleIngredientsList.openRecipeFile(model.recipeFileName)
                // Здесь будет вызываться функция для отправки имени файла в С++ слой для открытия файла
            }

        } // End of delegate block

    } // End of the ListView block for the list of recipes



    Button{
        id: toIngredientEntryWindowButton
        text: qsTr("Вернуться")
        anchors.bottom: parent.bottom
        anchors.left: resultRecipesList.left
        anchors.right: resultRecipesList.right
        onClicked: {
            stackView.pop();
        }

    // End of the Button block to return to the recipe request page
    }


    ScrollView{
        id: scrollRecipeText
        anchors.left: resultRecipesList.right
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 15

        TextArea{
            id: recipeDisplay
            anchors.fill: parent
            textFormat: TextEdit.RichText

        // End of the TextArea block to display the text of the recipe on the screen
        }

    // End of the ScrollView block for scrolling the text of the recipe
    }

// End Page resultRecipeWindow
}
