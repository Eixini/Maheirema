#include "headers/recipefilterproxymodel.h"

RecipeFilterProxyModel::RecipeFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
}

bool RecipeFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (!m_model) return false;
    bool result = true;
    for (auto & str: m_ingridients)
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

const QStringList &RecipeFilterProxyModel::ingridients() const
{
    return m_ingridients;
}

void RecipeFilterProxyModel::setIngridients(const QStringList &newIngridients)
{
    if (m_ingridients == newIngridients)
        return;
    m_ingridients = newIngridients;
    emit ingridientsChanged();
}
