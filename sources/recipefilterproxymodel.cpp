#include "headers/recipefilterproxymodel.h"
#include <QDebug>

RecipeFilterProxyModel::RecipeFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    m_model = new RecipeModel(this);
}

bool RecipeFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (!m_model) return false;
    bool result = true;
    for (auto & str: m_ingredients)
        result = result && m_model->haveIngredient(source_row, str);

    return result;
}

RecipeModel *RecipeFilterProxyModel::model() const
{
    return m_model;
}

void RecipeFilterProxyModel::setModel(RecipeModel *newModel)
{
    if (m_model == newModel)
        return;
    beginResetModel();
    m_model = newModel;
    endResetModel();
    emit modelChanged();
}

const QStringList &RecipeFilterProxyModel::ingredients() const
{
    qDebug() << "Call ingredients() method! Size:" << m_ingredients.size();
    return m_ingredients;
}

void RecipeFilterProxyModel::setIngredients(const QStringList &newIngridients)
{
    qDebug() << "Call setIngredients() method!";

    if (m_ingredients == newIngridients)
        return;
    m_ingredients = newIngridients;
    qDebug() << "setIngredients(): " << m_ingredients.size();
    emit ingredientsChanged();

}

void RecipeFilterProxyModel::updateRecipeData(QStringList ingData)
{
    qDebug() << "Call RecipeFilterProxyModel::updateRecipeData() method! Input data size: " << ingData.size();

    m_model->recipesLoaded(ingData);
    emit modelChanged();
}


