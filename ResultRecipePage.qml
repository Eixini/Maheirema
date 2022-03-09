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
        anchors.fill: parent

        ColumnLayout{
            id: recipesListAndButtons

            RecipeModel{
                id: recipeData
            }

            ListView{
                id: resultRecipesList
                Layout.alignment: Qt.AlignVCenter
                spacing: 5
                clip: true
                model: recipeData
                delegate: Rectangle{
                    id: recipeElement

                    height: 30
                    width: resultRecipesList.width
                    color: '#33FFDD'
                    radius: 5

                    Text {
                        anchors.fill: parent
                        Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                        text: model.recipeName
                    }

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            recipeDisplay.text = avaibleIngredientsList.openRecipeFile(model.recopeFileName)
                            console.log(avaibleIngredientsList.openRecipeFile(model.recopeFileName));
                            // Здесь будет вызываться функция для отправки имени файла в С++ слой для открытия файла
                        }
                    // End of the MouseArea code block for delegate
                    }

                // End of delegate block
                }

            // End of the ListView block for the list of recipes
            }



            Button{
                id: toIngredientEntryWindowButton
                text: qsTr("Вернуться")
                Layout.alignment: Qt.AlignBottom | Qt.AlignHCenter
                Layout.margins: 15
                onClicked: {
                    stackView.pop();
                }

            // End of the Button block to return to the recipe request page
            }

        // End of the ColumnLayout block
        }

        ScrollView{
            id: scrollRecipeText

            TextArea{
                id: recipeDisplay
                textFormat: TextEdit.RichText

            // End of the TextArea block to display the text of the recipe on the screen
            }

        // End of the ScrollView block for scrolling the text of the recipe
        }



    // End of RowLayout mainLayoutRecipeWindow
    }

// End Page resultRecipeWindow
}
