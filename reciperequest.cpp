#include "reciperequest.h"

#include <QDebug>
#include <cassert>
#include <iostream>
#include <QTimer>

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
    recipeDirPath = appFilePath + "/Maheirema" + "/Recipes";
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
    QDir recipesDir(recipeDirPath);

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
        qDebug() << "The recipe directory is empty!\n";
        setError(1);                   // Код 1 - директория с рецептами пуста
    }

}

void RecipeRequest::obtainingRecipesForAvailableIngredients(QStringList availableIngredients)
{

    qDebug() << "Number of Ingredients Introduced (in C++, before being placed in the set): " << availableIngredients.count();

    std::set<std::string> inputIngredients;
    for(auto i = 0; i < availableIngredients.count(); i++)
        inputIngredients.insert(availableIngredients.at(i).toStdString() );

    qDebug() << "Number of Ingredients Introduced (in C++): " << inputIngredients.size();       // Для отладки

    int recipeCounter = 0; // Counter containing the number of matching recipes | Iterator

    // Setting the target directory for iteration
    QDirIterator it(recipeDirPath, {"*.json"}, QDir::Files);

    qDebug() << recipeDirPath;
    QString jsonText;       // To store code from a JSON document
    while(it.hasNext()){
        it.next();

        QFileInfo fileInfo = it.fileInfo();
        QFile jsonFile(fileInfo.absoluteFilePath());
        qDebug() << fileInfo.fileName();
        jsonFile.open(QIODevice::ReadOnly);
        jsonText = jsonFile.readAll();
        jsonFile.close();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonText.toUtf8());
        QJsonObject jsonObject = jsonDocument.object();
        QString recipeName = jsonObject["name"].toString();
        qDebug() << recipeName;
        QJsonArray jsonArray = jsonObject["ingredients"].toArray();

        QList<QVariant> recipeIngredients = jsonArray.toVariantList();

        std::set<std::string> recipeIngredientsString;
        for(auto i = 0; i < recipeIngredients.count(); i++){
            recipeIngredientsString.insert(recipeIngredients.at(i).toString().toStdString());
        }

        // Checking ingredients from recipes and comparing them with entered ingredients
        if(std::includes(inputIngredients.begin(), inputIngredients.end() ,recipeIngredientsString.begin(), recipeIngredientsString.end())  ){
            qDebug() << recipeName << " - it's Recipe OK!";
            listSuitableRecipes.push_back(qMakePair(recipeName,fileInfo.baseName() + ".html"));
            qDebug() << "Data size in data-handler (includes): " << listSuitableRecipes.size();
            recipeCounter++;
        }
    // End of loop block for traversing the recipe directory
    }

    qDebug() << "Number of recipes that meet the condition: " << recipeCounter;
}

int RecipeRequest::errorCode() const
{
    return errorCode_;
}

QVector<QPair<QString, QString> > RecipeRequest::getListSuitableRecipes()
{
    qDebug() << "Data size in data-handler: " << listSuitableRecipes.size();
    return listSuitableRecipes;
}

QString RecipeRequest::openRecipeFile(QString fileName)
{
    QString recipeText;

    QFile recipeFile("recipeDirPath/" + fileName);
    recipeFile.open(QIODevice::ReadOnly);
    recipeText = recipeFile.readAll();
    recipeFile.close();

    return recipeText;
}

void RecipeRequest::setError(int newError)
{
    if(errorCode_ == newError)
        return;
    errorCode_ = newError;
    QTimer::singleShot(0, this, [this](){emit errorChanged();});

}
