#include "headers/recipemodel.h"

#include <QDebug>

RecipeModel::RecipeModel(QObject *parent) : QAbstractListModel(parent)
{

}

int RecipeModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return m_preparedRecipeData.size();
}

QVariant RecipeModel::data(const QModelIndex &index, int role) const
{
    auto & recipeData = m_preparedRecipeData.at(index.row());

    switch(role){
    case RecipeNameRole:
        return recipeData.recipeName;
    case RecipeFileNameRole:
        return recipeData.recipeFileName;
    case NationalKitchenRole:
        return recipeData.nationalKitchen;
    case DishTypeRole:
        return recipeData.dishType;
    }

    return QVariant();
}

QHash<int, QByteArray> RecipeModel::roleNames() const
{
    static QHash<int, QByteArray> roles {
        {RecipeNameRole, "recipeName"},
        {RecipeFileNameRole, "recipeFileName"},
        {NationalKitchenRole, "nationalKitchen"},
        {DishTypeRole, "dishType"}
    };

    return roles;
}

bool RecipeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == RecipeNameRole) {
        m_preparedRecipeData[index.row()].recipeName = value.toString();
        return true;
    } else if (role == RecipeFileNameRole){
        m_preparedRecipeData[index.row()].recipeFileName= value.toString();
        return true;
    } else if (role == NationalKitchenRole){
        m_preparedRecipeData[index.row()].nationalKitchen = value.toString();
        return true;
    } else if (role == DishTypeRole) {
        m_preparedRecipeData[index.row()].dishType = value.toString();
        return true;
    }
    return false;
}

bool RecipeModel::haveIngredient(int recipe_index, QString ingredient)
{
    return m_preparedRecipeData[recipe_index].ingredients.contains(ingredient);
}

void RecipeModel::setIntroducedIngredients(QStringList availableIngredients)
{
    availableIngredients_ = availableIngredients;
}

QStringList RecipeModel::getIntroducedIngredients()
{
    return availableIngredients_;
}

void RecipeModel::recipesLoaded(QStringList ingData){
    suitableRecipeData = new RecipeRequest(this);

    qDebug() << "Call RecipeModel::recipeLoaded! Input data size: " << ingData.size();

    auto receivedData = suitableRecipeData->obtainingRecipesForAvailableIngredients(ingData);
    qDebug() << "data from =" << receivedData.size();
    beginInsertRows(QModelIndex(), m_preparedRecipeData.size() , m_preparedRecipeData.size() + receivedData.size());
    for(auto i = 0; i < receivedData.size(); i++) {
        RecipeData rData;
        rData.recipeName = receivedData[i].recipeName;
        rData.recipeFileName = receivedData[i].recipeFileName;
        rData.dishType = receivedData[i].dishType;
        rData.nationalKitchen = receivedData[i].nationalKitchen;
        rData.ingredients = receivedData[i].ingredients;

        m_preparedRecipeData.append(rData);

    }
    qDebug() << "New Data size in model: " << m_preparedRecipeData.size();
    endInsertRows();

}

int RecipeModel::recipeCount() const    {   return m_preparedRecipeData.size();   }

RecipeModel::~RecipeModel(){}
