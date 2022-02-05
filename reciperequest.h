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
#include <QDir>
#include <QDirIterator>
#include <QStringList>

#include <algorithm>
#include <cctype>

class RecipeRequest : public QObject
{

    int errorCode_;     // Для передачи значения в QML

private:

    Q_OBJECT
    Q_PROPERTY(QStringList avaibleIngredients WRITE obtainingRecipesForAvailableIngredients)
    Q_PROPERTY(int errorCode READ errorCode NOTIFY errorChanged)

    // Для хранения рецептов по ингредиентам (Ингредиенты - ключ, Рецепт - значение)
    std::map<QStringList, QString> recipes_;

    QList<std::set<std::string> > respondRecipesList;       // Для хранения рецептов, удовлетворяющих условию (по имеющимся ингредиентам)

    QString appFilePath;                 // Путь для хранения файлов приложения

    // Инициализация рецептов и списка ингредиентов для доступа к ним
    void recipeInitialization();

    // Проверка существования директории приложения
    void checkingApplicationDirectory();

    // Проверка на различные ошибки (наличие файлов в директории, их расширение и т.д)
    void errorChecker();

    std::set<std::string> inputIngredients;

public:

    explicit RecipeRequest(QObject *parent = nullptr);

    // Функция для вызова извне (QML), принимающая список ингридиентов, и выдающая доступные рецепты, если таковые есть
    Q_INVOKABLE void obtainingRecipesForAvailableIngredients(QStringList availableIngredients);

    int errorCode() const;

public slots:

    void setError(int newError);

signals:

    void availabilityRecipes();

    void errorChanged();
};

#endif // RECIPEREQUEST_H
