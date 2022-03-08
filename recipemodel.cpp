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
    switch(role){
    case RecipeNameRole:
        return QVariant(QString::fromStdString(recipeData.at(index.row()).first) );
    case RecipeFileNameRole:
        return QVariant(QString::fromStdString(recipeData.at(index.row()).second) );
    default:
        return QVariant();

    }
}

QHash<int, QByteArray> RecipeModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[RecipeNameRole] = "recipeName";
    roles[RecipeFileNameRole] = "recipeFileName";

    return roles;
}
