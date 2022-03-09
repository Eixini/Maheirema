#include "recipemodel.h"
#include "reciperequest.h"

RecipeModel::RecipeModel()
{
    RecipeRequest recipeHandlerClass;
    recipeData = recipeHandlerClass.getListSuitableRecipes();
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
    case RecipeNameRole:
        qDebug() << "In model: " << QVariant(QString(recipeData.at(index.row()).first) );
        return QVariant(QString(recipeData.at(index.row()).first) );
    case RecipeFileNameRole:
        return QVariant(QString(recipeData.at(index.row()).second) );
    default:
        return QVariant();

    }
}

QHash<int, QByteArray> RecipeModel::roleNames() const
{
    static QHash<int, QByteArray> roles {
        {RecipeNameRole, "recipeName"},
        {RecipeFileNameRole, "recipeFileName"}
    };

    return roles;
}
