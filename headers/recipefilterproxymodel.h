#ifndef RECIPEFILTERPROXYMODEL_H
#define RECIPEFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QQmlListProperty>

#include "headers/recipemodel.h"
#include "headers/reciperequest.h"

class RecipeFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY(RecipeModel* model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(QStringList ingredients READ ingredients WRITE setIngredients NOTIFY ingredientsChanged)

public:
    RecipeFilterProxyModel(QObject * parent = nullptr);

    RecipeModel *model() const;
    void setModel(RecipeModel *newModel);
    const QStringList &ingredients() const;
    void setIngredients(const QStringList &newIngridients);

    Q_INVOKABLE void updateRecipeData(QStringList ingData);

signals:

    void modelChanged(RecipeModel* Model);
    void ingredientsChanged();

private:

    RecipeModel *m_model;
    QStringList m_ingredients;

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

};

#endif // RECIPEFILTERPROXYMODEL_H
