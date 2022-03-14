import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import RecipeModelModule

Page{
    id: resultRecipeWindow
    title: "Mahεirεma"

    Image {
        id: backgroundImage
        source: "qrc:/maheirema_resource/image/image/mh_background.png"
        width: 1920
        height: 1080
        visible: true
        anchors.fill: parent

    // End of BACKGROUND image block
    }


    RowLayout{
        id: mainLayoutRecipeWindow
//        anchors.fill: parent
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        ColumnLayout{
            id: recipesListAndButtons

            RecipeModel{
                id: recipeData
            }

            ListView{
                id: resultRecipesList
                width: 200
                anchors.top: parent.top
                anchors.bottom: toIngredientEntryWindowButton.top
                anchors.left: parent.left
                spacing: 5
                //clip: true


                header: Rectangle{
                    width: parent.width
                    height: 50
                    color: '#00A287'
                    Text {
                        id: viewHeaderText
                        anchors.centerIn: parent
                        text: qsTr("Найденный рецепты")
                    }
                }

                model: recipeData

//                onCountChanged: {
//                    console.log("! ============ DATA CHANGED ============ !");
//                    console.log("DATA SIZE: " + model.recipeCount);
//                }

                delegate: Rectangle{
                    id: recipeElement

                    height: 30
                    width: 100
                    color: '#33FFDD'
                    radius: 5

                    Text {
                        id: recipeNameText
                        anchors.fill: parent
                        //Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                        text: model.recipeName
                    }

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            recipeDisplay.text = avaibleIngredientsList.openRecipeFile(model.recipeFileName)
                            // Здесь будет вызываться функция для отправки имени файла в С++ слой для открытия файла
                        }
                    // End of the MouseArea code block for delegate
                    }

                // End of delegate block
                }

                Timer{
                    id: timerForUpdateView
                    interval: 1000
                    repeat: false

                    onTriggered: {
                        recipeElement.recipeNameText.text = model.recipeName;
                    }

                // End of Timer code block
                }

                Connections{
                    target: recipeData
                    function onCountChanged() {
                        console.log("! ============ DATA CHANGED ============ !");
                        console.log("NEW SUITABLE RECIPE DATA SIZE: ", recipeData.recipeCount());
                         //recipeNameText = resultRecipesList.model.recipeName;
                    }
                // End of the Connections block
                }

            // End of the ListView block for the list of recipes
            }



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

        // End of the ColumnLayout block
        }

        ScrollView{
            id: scrollRecipeText
            anchors.left: resultRecipesList.right
            anchors.top: parent.top
            anchors.right: parent.right
             anchors.bottom: parent.bottom

            TextArea{
                id: recipeDisplay
                anchors.fill: parent
                textFormat: TextEdit.RichText

            // End of the TextArea block to display the text of the recipe on the screen
            }

        // End of the ScrollView block for scrolling the text of the recipe
        }



    // End of RowLayout mainLayoutRecipeWindow
    }

// End Page resultRecipeWindow
}
