import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

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
            anchors.bottom: parent

            ListView{
                id: resultRecipesList

            // End of the ListView block for the list of recipes
            }

            Button{
                id: toIngredientEntryWindowButton
                text: qsTr("Вернуться")
                anchors.bottom: parent
                Layout.margins: 15
                onClicked: {
                    stackView.pop();
                }

            // End of the Button block to return to the recipe request page
            }

        // End of the ColumnLayout block
        }

    // End of RowLayout mainLayoutRecipeWindow
    }

// End Page resultRecipeWindow
}
