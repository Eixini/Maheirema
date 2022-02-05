#include "reciperequest.h"
#include <QJsonDocument>

#include <QDebug>
#include <cassert>
#include <iostream>

// ----------- В целях отладки

    // Фунция Константина (для проверки)
    template<typename A, typename B, bool Debug = true>
    bool HasAllIngredients(A& recipe, B& ingredients) {
        const bool result = std::includes(ingredients.begin(), ingredients.end(), recipe.begin(), recipe.end());

        if constexpr (Debug) {
            assert(std::is_sorted(ingredients.begin(), ingredients.end()));
            assert(std::is_sorted(recipe.begin(), recipe.end()));

            std::cout << "HasAllIngredients:\n";

            std::cout << "   Recipe: ";
            for (auto& v: recipe) {
                std::cout << v << ' ';
            }
            std::cout << '\n';

            std::cout << "   Ingredients: ";
            for (auto& v: ingredients) {
                std::cout << v << ' ';
            }
            std::cout << '\n';

            std::cout << "   Result: " << result << '\n' << '\n';
        }

        return result;
    }
// ---------

RecipeRequest::RecipeRequest(QObject *parent) : QObject(parent)
{
    // ---------------------------- ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ ------------------------------
    appFilePath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);    // Путь для хранения файлов приложения


    // +++++++++++++++++++++++++++++++ ФУНКЦИОНАЛ +++++++++++++++++++++++++++++++++++++++
    checkingApplicationDirectory();             // Вызов функции проверки существования директории приложения
    connect(this, &RecipeRequest::errorChanged, this, [&]() { qDebug() << "\nThe signal is emitted !!!\n";});
    errorChecker();                     // Вызов функции в которой генерируется сигнал для QML

}

void RecipeRequest::checkingApplicationDirectory(){

    // Проверка на существование директории приложения
    QDir appDir(appFilePath + "/Maheirema");    // Директория приложения

    if(!appDir.exists()){
        qDebug() << "Application directory does not exist! A new one will be created.";

        appDir.setPath(appFilePath);        // Установка пути для директории приложения
        appDir.mkdir("Maheirema");          // Создание директории приложения

        if(QDir(appFilePath + "/Maheirema").exists())
            qDebug() << "Application directory created successfully!";
    }
    else{
        qDebug() << "Application directory exist!";
    }

    // Проверка на существование директории рецептов
    QDir recipesDir(appFilePath + "/Maheirema" + "/Recipes");

    if(!recipesDir.exists()){
        qDebug() << "Recipes directory does not exist! A new one will be created.";

        recipesDir.setPath(appFilePath + "/Maheirema");
        recipesDir.mkdir("Recipes");

        if(QDir(appFilePath + "/Maheirema").exists())
            qDebug() << "Recipes directory created successfully!";
    }
    else{
        qDebug() << "Recipes directory exist!";
    }

}

void RecipeRequest::errorChecker()
{
    /*
     В данной функции проверяется, существую ли рецепты в директории для рецептов
     Если рецепты существуют и имеют корректный формат, то функция возвращает true , а иначе false
    */

    // Проверка, пуста ли директория с рецептами или нет
    if(QDir(appFilePath + "/Maheirema/Recipes").isEmpty()){
        qDebug() << "The recipe directory is empty!";
        setError(1);                   // Код 1 - директория с рецептами пуста
    }

}



void RecipeRequest::recipeInitialization()
{

}

void RecipeRequest::obtainingRecipesForAvailableIngredients(QStringList availableIngredients)
{
    recipeInitialization();     // Вызов метода , инициализирующий рецепты

    qDebug() << "Number of Ingredients Introduced (in C++, before being placed in the set): " << availableIngredients.count();

    std::set<std::string> inputIngredients;
    for(auto i = 0; i < availableIngredients.count(); i++)
        inputIngredients.insert(availableIngredients.at(i).toStdString() );

    qDebug() << "Number of Ingredients Introduced (in C++): " << inputIngredients.size();       // Для отладки


//    for(auto i = 0; i < Recipes.count(); i++)
//    {
//        if(std::includes(Recipes[i].begin(), Recipes[i].end(), inputIngredients.begin(), inputIngredients.end() )  )
//            respondRecipesList.append(Recipes[i]);  // Если рецепт подходит, то добавляется в контейнер результатов
//    }

    // Отладочный вариант
//    for(auto i = 0; i < Recipes.count(); i++)
//    {
//        if(HasAllIngredients(Recipes.at(i),inputIngredients)  )
//            respondRecipesList.append(Recipes[i]);  // Если рецепт подходит, то добавляется в контейнер результатов
//    }


    qDebug() << "Number of recipes that meet the condition: " << respondRecipesList.count();
}

int RecipeRequest::errorCode() const
{
    return errorCode_;
}

void RecipeRequest::setError(int newError)
{
    if(errorCode_ == newError)
        return;
    errorCode_ = newError;
    emit errorChanged();
}
