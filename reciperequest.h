#ifndef RECIPEREQUEST_H
#define RECIPEREQUEST_H

#include <QObject>
#include <QQmlParserStatus>
#include <utility>
#include <set>
#include <string>
#include <QSet>
#include <QString>
#include <QPair>
#include <QVector>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#include <QDirIterator>
#include <QStringList>
#include <QIODevice>
#include <QFileInfo>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include <algorithm>
#include <cctype>

class RecipeRequest : public QObject //, public QQmlParserStatus
{

    int errorCode_;     // Для передачи значения в QML

private:

    Q_OBJECT
//    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QStringList avaibleIngredients WRITE obtainingRecipesForAvailableIngredients)
    Q_PROPERTY(int errorCode READ errorCode NOTIFY errorChanged)

    QString recipeDirPath; // Recipe directory
    // To store recipes that meet the condition (by available ingredients)
    QVector<QPair<QString, QString> > listSuitableRecipes;
    QList<std::set<std::string> > respondRecipesList;

    QString appFilePath;                 // Путь для хранения файлов приложения

    // Проверка существования директории приложения
    void checkingApplicationDirectory();

    // Проверка на различные ошибки (наличие файлов в директории, их расширение и т.д)
    void errorChecker();

    std::set<std::string> inputIngredients;


public:

    explicit RecipeRequest(QObject *parent = nullptr);

    // Функция для вызова извне (QML), принимающая список ингридиентов, и выдающая доступные рецепты, если таковые есть
    Q_INVOKABLE void obtainingRecipesForAvailableIngredients(QStringList availableIngredients);
    Q_INVOKABLE QString openRecipeFile(QString fileName);

    int errorCode() const;

//    void classBegin() override;
//    void componentComplete() override;

    // To pass the required recipe data to the model
    QVector<QPair<QString, QString> > getListSuitableRecipes();

public slots:

    void setError(int newError);

signals:

    //void availabilityRecipes();
    void errorChanged();
};

#endif // RECIPEREQUEST_H
