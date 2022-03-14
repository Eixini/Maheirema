#ifndef RECIPEMODEL_H
#define RECIPEMODEL_H

#include <QAbstractListModel>
#include <QQmlParserStatus>
#include <QModelIndex>
#include <QString>
#include <QVector>
#include <QPair>

class RecipeModel : public QAbstractListModel // , public QQmlParserStatus
{
    Q_OBJECT
//    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(int recipeCount READ recipeCount NOTIFY countChanged)
public:

    RecipeModel(QObject *parent = nullptr);
    ~RecipeModel();
    enum Roles{
        RecipeNameRole = Qt::UserRole,
        RecipeFileNameRole
    };

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

//    void classBegin() override;
//    void componentComplete() override;

    Q_INVOKABLE QVector<QPair<QString, QString> > recipes(){
        return recipeData;
    }

public slots:

    void recipesLoaded(QVector<QPair<QString, QString> > newData);
    int recipeCount() const;

private:

    QVector<QPair<QString, QString> > recipeData;

signals:

    void countChanged();

};

#endif // RECIPEMODEL_H
