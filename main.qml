import QtQuick //2.12
import QtQuick.Window //2.12
import QtQuick.Layouts //1.3
import QtQuick.Controls //2.12

import RecipeRequestModule 1.0      // Модуль из C++

/*
   Заметки разработки:
    - Добавить возможность менять ращмер шрифта (пользователю);

    ВАЖНО !!!!
    Исключить возможность ввода повторного раза одного и того же ингредиента !!!
*/

ApplicationWindow {

    id: windowMain
    width: 640
    //height: 480
    visible: true
    title: "Mahεirεma";

    RecipeRequest{
        id: avaibleIngredientsList

        onErrorChanged: {
            console.log("Error num: " + avaibleIngredientsList.errorCode)

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
        }
    }

    StackView{
        id: stackView
        anchors.fill: parent
        initialItem: ingredientEntryPage
    }

    IngredientEntryPage{
        id: ingredientEntryPage
    }

    ResultRecipePage{
        id: resultRecipePage
        visible: false
    }

    // --------------------- КОНЕЦ ГЛАВНОГО ОКНА ПРИЛОЖЕНИЯ ----------------------
}

