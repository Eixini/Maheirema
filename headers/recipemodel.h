#ifndef RECIPEMODEL_H
#define RECIPEMODEL_H

#include <QAbstractListModel>
#include <QQmlParserStatus>
#include <QQmlListProperty>
#include <QModelIndex>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QPair>

#include "headers/reciperequest.h"

class RecipeModel : public QAbstractListModel // , public QQmlParserStatus
{
    Q_OBJECT
//    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(int recipeCount READ recipeCount NOTIFY countChanged)


    // Data structure for storing recipe information
    struct RecipeData {
        QString recipeName;
        QString recipeFileName;
        QString nationalKitchen;
        QString dishType;
        QVector<QString> ingredients;
    };

public:

    RecipeModel(QObject *parent = nullptr);
    ~RecipeModel();
    enum Roles{
        RecipeNameRole = Qt::UserRole + 1,
        RecipeFileNameRole,
        NationalKitchenRole,
        DishTypeRole
    };

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

//    void classBegin() override;
//    void componentComplete() override;

    Q_INVOKABLE QVector <RecipeData> recipes(){
        return m_preparedRecipeData;
    }

    bool haveIngredient(int recipe_index, QString ingredient);

    Q_INVOKABLE void setIntroducedIngredients(QStringList availableIngredients);
    QStringList getIntroducedIngredients();

public slots:

    //void recipesLoaded(QVector<QPair<QString, QString> > newData);
    void recipesLoaded();
    int recipeCount() const;

private:

    QStringList availableIngredients_;
    RecipeRequest* suitableRecipeData;
    QVector <RecipeData> m_preparedRecipeData;

signals:

    void countChanged();

};

#endif // RECIPEMODEL_H
