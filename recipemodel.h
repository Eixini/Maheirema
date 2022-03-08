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
        RecipeNameRole = Qt::UserRole + 1,
        RecipeFileNameRole
    };

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

private:

    QVector<std::pair<std::string, std::string> > recipeData;

};

#endif // RECIPEMODEL_H
