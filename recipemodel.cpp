#include "recipemodel.h"
#include "reciperequest.h"

#include <QTimer>

RecipeModel::RecipeModel(QObject *parent) : QAbstractListModel(parent)
{
    RecipeRequest recipeHandlerClass;
    recipeData = recipeHandlerClass.getListSuitableRecipes();

    // { debug
    recipeData.push_back(qMakePair("Test Recipe1", "testrecipe1.html"));
    recipeData.push_back(qMakePair("Test Recipe2", "testrecipe2.html"));
    recipeData.push_back(qMakePair("Test Recipe3", "testrecipe3.html"));
    // } debug

    QTimer *recipeLoadTimer = new QTimer(this);

    connect(recipeLoadTimer, &QTimer::timeout, this, &RecipeModel::recipesLoaded);
    recipeLoadTimer->start(2000);

    qDebug() << "Data size in model: " << recipeData.size();
}

int RecipeModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())    {   return 0;   }
    return recipeData.size();
}

QVariant RecipeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
        qDebug() << "In model: invalid index!";
    switch(role){
    case Qt::DisplayRole:
    case RecipeNameRole:
        qDebug() << "In model (RecipeNameRole): " << recipeData.at(index.row()).first;
        qDebug() << "In model (RecipeNameRole index): " << QVariant(index);
        return recipeData.at(index.row()).first;
    case RecipeFileNameRole:
        qDebug() << "In model(RecipeFileNameRole): " << recipeData.at(index.row()).second;
        return recipeData.at(index.row()).second;
    }

    return QVariant();
}

QHash<int, QByteArray> RecipeModel::roleNames() const
{
    static QHash<int, QByteArray> roles {
        {RecipeNameRole, "recipeName"},
        {RecipeFileNameRole, "recipeFileName"}
    };

    return roles;
}

void RecipeModel::recipesLoaded(){

    const int count = recipeData.count();

    const QModelIndex startIndex = index(0, 0);
    const QModelIndex endIndex   = index(count - 1, 0);

    emit dataChanged(startIndex, endIndex, QVector<int>() << RecipeNameRole << RecipeFileNameRole);
}
