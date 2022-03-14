#include "recipemodel.h"
#include "reciperequest.h"

#include <QDebug>
#include <QTimer>

RecipeModel::RecipeModel(QObject *parent) : QAbstractListModel(parent)
{
    // { debug
    recipeData.push_back({"Test Recipe1", "testrecipe1.html"});
    recipeData.push_back({"Test Recipe2", "testrecipe2.html"});
    recipeData.push_back({"Test Recipe3", "testrecipe3.html"});
    // } debug

    qDebug() << "Data size in model: " << recipeData.size();
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
        qDebug() << "In model (RecipeNameRole): " << recipeData.at(index.row()).first;
        qDebug() << "In model (RecipeNameRole index): " << QVariant(index);
        return recipeData.at(index.row()).first;
    case RecipeFileNameRole:
        qDebug() << "In model(RecipeFileNameRole): " << recipeData.at(index.row()).second;
        return recipeData.at(index.row()).second;
    }

    return QVariant();
}

QHash<int, QByteArray> RecipeModel::roleNames() const
{
    static QHash<int, QByteArray> roles {
        {RecipeNameRole, "recipeName"},
        {RecipeFileNameRole, "recipeFileName"}
    };

    return roles;
}

void RecipeModel::recipesLoaded(QVector<QPair<QString, QString> > newData){

    const int count = recipeData.count();
    const int inputDataCount = newData.size();

    beginInsertRows(QModelIndex(), index(0, 0).row(),  index(count + newData.size(), 0).row());
    for(auto i = 0; i < newData.size(); i++)
        recipeData.push_back(newData.at(i));
    endInsertRows();

    const QModelIndex startIndex = index(0, 0);
    const QModelIndex endIndex   = index(count - 1, 0);

    emit dataChanged(startIndex, endIndex, QVector<int>() << RecipeNameRole << RecipeFileNameRole);

    const int newDataCouny = recipeData.count();

    emit countChanged();

    qDebug() << "Data size BEFORE update: " << count;
    qDebug() << "Input data size: " << inputDataCount;
    qDebug() << "Data size AFTER update: " << newDataCouny;
}

int RecipeModel::recipeCount() const    {   return recipeData.size();   }

RecipeModel::~RecipeModel(){}
