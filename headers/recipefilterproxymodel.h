#ifndef RECIPEFILTERPROXYMODEL_H
#define RECIPEFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QQmlListProperty>

#include "headers/recipemodel.h"

class RecipeFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY(RecipeModel* model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(QStringList ingridients READ ingridients WRITE setIngridients NOTIFY ingridientsChanged)

public:
    RecipeFilterProxyModel(QObject * parent = nullptr);

    RecipeModel *model() const;
    void setModel(RecipeModel *newModel);
    const QStringList &ingridients() const;
    void setIngridients(const QStringList &newIngridients);

signals:

    void modelChanged();
    void ingridientsChanged();

private:

    RecipeModel *m_model;
    QStringList m_ingridients;

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

};

#endif // RECIPEFILTERPROXYMODEL_H
