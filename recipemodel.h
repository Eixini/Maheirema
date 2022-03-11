#ifndef RECIPEMODEL_H
#define RECIPEMODEL_H

#include <QAbstractListModel>
#include <QModelIndex>
#include <QString>
#include <QVector>
#include <QPair>

class RecipeModel : public QAbstractListModel
{
    Q_OBJECT
public:

    RecipeModel(QObject *parent = nullptr);

    enum Roles{
        RecipeNameRole = Qt::UserRole,
        RecipeFileNameRole
    };

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE QVector<QPair<QString, QString> > recipes(){
        return recipeData;
    }

private:

    QVector<QPair<QString, QString> > recipeData;

private slots:

    void recipesLoaded();

};

#endif // RECIPEMODEL_H
