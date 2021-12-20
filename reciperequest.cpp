#include "reciperequest.h"
#include <QJsonDocument>

#include <QDebug>
#include <cassert>
#include <iostream>

// ----------- В целях отладки
    QString desktopLoc = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

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

void RecipeRequest::recipeInitialization()
{
    // Возможно создание и инициализация ингредиентов с некого файла ... JSON ?

    // Пока что в целях отладки
    TestRecipe1.insert("Potato");
    TestRecipe1.insert("Tomato");

    TestRecipe2.insert("Potato");
    TestRecipe2.insert("Tomato");
    TestRecipe2.insert("Bell pepper");

    TestRecipe3.insert("Potato");
    TestRecipe3.insert("Carrot");
    TestRecipe3.insert("Tomato");

    TestRecipe4.insert("Tomato");
    TestRecipe4.insert("Cucumber");
    TestRecipe4.insert("Sour cream");

    TestRecipe5.insert("Potato");
    TestRecipe5.insert("Onion");

    TestRecipe6.insert("Tomato");
    TestRecipe6.insert("Bell pepper");
    TestRecipe6.insert("Sour cream");
    TestRecipe6.insert("Cheese");

    TestRecipe7.insert("Cheese");
    TestRecipe7.insert("Egg");
    TestRecipe7.insert("Bacon");

    TestRecipe8.insert("Potato");
    TestRecipe8.insert("Meat");

    TestRecipe9.insert("Meat");
    TestRecipe9.insert("Onion");
    TestRecipe9.insert("Tomato");

    TestRecipe10.insert("Potato");

    TestRecipe11.insert("Tomato");
    TestRecipe11.insert("Salt");
    TestRecipe11.insert("Garlic");

    Recipes.push_back(TestRecipe1);
    Recipes.push_back(TestRecipe2);
    Recipes.push_back(TestRecipe3);
    Recipes.push_back(TestRecipe4);
    Recipes.push_back(TestRecipe5);
    Recipes.push_back(TestRecipe6);
    Recipes.push_back(TestRecipe7);
    Recipes.push_back(TestRecipe8);
    Recipes.push_back(TestRecipe9);
    Recipes.push_back(TestRecipe10);
    Recipes.push_back(TestRecipe11);
}

void RecipeRequest::obtainingRecipesForAvailableIngredients(QStringList availableIngredients)
{
    recipeInitialization();     // Вызов метода , инициализирующий рецепты

    qDebug() << "Количество введенных ингредиентов (in C++, до помещения в множество): " << availableIngredients.count();

    std::set<std::string> inputIngredients;
    for(auto i = 0; i < availableIngredients.count(); i++)
        inputIngredients.insert(availableIngredients.at(i).toStdString() );

    qDebug() << "Количество введенных ингредиентов (in C++): " << inputIngredients.size();       // Для отладки


//    for(auto i = 0; i < Recipes.count(); i++)
//    {
//        if(std::includes(Recipes[i].begin(), Recipes[i].end(), inputIngredients.begin(), inputIngredients.end() )  )
//            respondRecipesList.append(Recipes[i]);  // Если рецепт подходит, то добавляется в контейнер результатов
//    }

    // Раз уж на то пошло, пробую ТУПОЙ тест алгоритма, так как мб трабла в хранении данных
    if(HasAllIngredients(TestRecipe1,inputIngredients) )
        respondRecipesList.append(TestRecipe1);

    if(HasAllIngredients(TestRecipe2,inputIngredients) )
        respondRecipesList.append(TestRecipe2);

    if(HasAllIngredients(TestRecipe3,inputIngredients) )
        respondRecipesList.append(TestRecipe3);

    if(HasAllIngredients(TestRecipe4,inputIngredients)  )
        respondRecipesList.append(TestRecipe4);

    if(HasAllIngredients(TestRecipe5,inputIngredients)  )
        respondRecipesList.append(TestRecipe5);

    if(HasAllIngredients(TestRecipe6,inputIngredients)  )
        respondRecipesList.append(TestRecipe6);

    if(HasAllIngredients(TestRecipe7,inputIngredients)  )
        respondRecipesList.append(TestRecipe7);

    if(HasAllIngredients(TestRecipe8,inputIngredients) )
        respondRecipesList.append(TestRecipe8);

    if(HasAllIngredients(TestRecipe9,inputIngredients)  )
        respondRecipesList.append(TestRecipe9);

    if(HasAllIngredients(TestRecipe10,inputIngredients) )
        respondRecipesList.append(TestRecipe10);

    if(HasAllIngredients(TestRecipe11,inputIngredients)  )
        respondRecipesList.append(TestRecipe11);

    qDebug() << "Количество рецептов, удовлетворяющих условию: " << respondRecipesList.count();
}
