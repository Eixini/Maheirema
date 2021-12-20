#ifndef RECIPEREQUEST_H
#define RECIPEREQUEST_H

#include <QObject>
#include <map>
#include <set>
#include <string>
#include <QSet>
#include <QString>
#include <QVector>
#include <QFile>
#include <QStandardPaths>
#include <QStringList>

#include <algorithm>
#include <cctype>

class RecipeRequest : public QObject
{
private:

    Q_OBJECT
    Q_PROPERTY(QStringList avaibleIngredients WRITE obtainingRecipesForAvailableIngredients)

    // Для хранения рецептов по ингредиентам (Ингредиенты - ключ, Рецепт - значение)
    std::map<QStringList, QString> recipes_;

    QList<std::set<std::string> > respondRecipesList;       // Для хранения рецептов, удовлетворяющих условию (по имеющимся ингредиентам)

    // Инициализация рецептов и списка ингредиентов для доступа к ним
    void recipeInitialization();

    // Пока что в целях отладки
        QVector<std::set<std::string> > Recipes;    // Имеющиеся рецепты

        std::set <std::string> TestRecipe1;
        std::set <std::string> TestRecipe2;
        std::set <std::string> TestRecipe3;
        std::set <std::string> TestRecipe4;
        std::set <std::string> TestRecipe5;
        std::set <std::string> TestRecipe6;
        std::set <std::string> TestRecipe7;
        std::set <std::string> TestRecipe8;
        std::set <std::string> TestRecipe9;
        std::set <std::string> TestRecipe10;
        std::set <std::string> TestRecipe11;

    std::set<std::string> inputIngredients;

public:

    // Функция для вызова извне (QML), принимающая список ингридиентов, и выдающая доступные рецепты, если таковые есть
    Q_INVOKABLE void obtainingRecipesForAvailableIngredients(QStringList availableIngredients);

};

#endif // RECIPEREQUEST_H
