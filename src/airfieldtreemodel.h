#ifndef AIRFIELDTREEMODEL_H
#define AIRFIELDTREEMODEL_H

#include <QAbstractItemModel>
#include <airfield.h>
#include "treeitembase.h"

class AirfieldTreeModel : public QAbstractItemModel
{
public:
    AirfieldTreeModel(const TAirfields& airfieldData,  QObject *parent = nullptr);
    virtual ~AirfieldTreeModel();

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    TreeItemBase* getItemData(const QModelIndex &index);

private:
    void setupModelData(const TAirfields& airfieldData, TreeItemBase *parent);

    TreeItemBase *rootItem;
};

#endif // AIRFIELDTREEMODEL_H
