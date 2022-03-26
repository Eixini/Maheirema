import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import RecipeRequestModule 1.0
import RecipeModel

/*
   Заметки разработки:
    - Добавить возможность менять ращмер шрифта (пользователю);

    ВАЖНО !!!!
    Исключить возможность ввода повторного раза одного и того же ингредиента !!!
*/

ApplicationWindow {

    property RecipeModel model

    id: windowMain
    width: 640
    //height: 480
    visible: true
    title: "Mahεirεma";

    property alias statusText: statusLine.text

    RecipeModel{
        id: recipeData
        onDataChanged: {console.log("Data in model Changed!")}
    }

    // The toolbar is needed for application settings, settings and display of data, information and help on the application
    header: ToolBar{
        id: toolBar

        RowLayout{
            anchors.fill: parent

            ToolButton{
                text: qsTr("About application")
                onClicked: {
                    stackView.push(aboutApplicationPageComponent.createObject());
                }

            } // End of toolbar button code block - application information

        } // End of layout block for toolbar buttons

    } // End of toolbar code block

    RecipeRequest{
        id: avaibleIngredientsList

        onErrorChanged: {
            console.log("Error num: " + avaibleIngredientsList.errorCode)
            statusLine.text = "Error num: " + avaibleIngredientsList.errorCode;
            // В зависимости от кода ошибки, выводятся соотвествующие предупреждения

            /*  Код ошибки 1 - Описание
                Если errorCode = 1 - "Необходимо загрузить архив рецептов"
                Необходимо скачать архив с рецептами.
                Далее открыть специальную вкладку в приложении, где появится специальное окно (что то вроде QFileDialog.
                Выбрать архив с рецептами и нажать "ОК". После этого, идет провекра,
                является ли архив - архив с рецептами или же это совсем другой архив.
                Если же это другой архив - то выдается другой код ошибки.
                В случае, если архив является архивом с рецептами, то рецепты распаковываются в директорию для хранения рецептов.
                Затем, идет перепроверка.
            */
        } // End of Error Discription block
    } // End of RecipeRequest code

    StackView{
        id: stackView
        anchors.fill: parent
        initialItem: ingredientEntryPageComponent.createObject()
    }

    Component {
        id: ingredientEntryPageComponent

        IngredientEntryPage{
            id: ingredientEntryPage
            visible: true
            recipeModel: recipeData
        }
    } // End of Component for "ingredientEntryPage"



    Component {
        id: aboutApplicationPageComponent

        AboutApplicationPage{
            id: aboutApplicationPage
            visible: false
        }
    } // End of Component for "AboutApplicationPage"

    Component {
        id: resultRecipePageComponent

        ResultRecipePage{
            id: resultRecipePage
            visible: false
            model: recipeData
        }
    } // End of Component for "ResultRecipePage"

    // Footer for displaying status information, such as errors filling data, opening a document, etc.
    footer: Label{
        id: statusLine
        text: ""

    } // End of Footer block to display status information

    // --------------------- КОНЕЦ ГЛАВНОГО ОКНА ПРИЛОЖЕНИЯ ----------------------
}

