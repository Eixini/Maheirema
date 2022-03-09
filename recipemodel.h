#ifndef RECIPEMODEL_H
#define RECIPEMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QString>
#include <QVector>
#include <set>
#include <string>
#include <vector>
#include <QPair>

class RecipeModel : public QAbstractListModel
{
    Q_OBJECT
public:

    RecipeModel();

    enum Roles{
        RecipeNameRole = Qt::UserRole,
        RecipeFileNameRole
    };

    Q_INVOKABLE int rowCount(const QModelIndex &parent) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;

private:

    QVector<QPair<QString, QString> > recipeData;

};

#endif // RECIPEMODEL_H
