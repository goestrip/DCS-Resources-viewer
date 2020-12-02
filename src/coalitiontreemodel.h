#ifndef COALITIONTREEMODEL_H
#define COALITIONTREEMODEL_H

#include <QAbstractItemModel>
#include "treeitembase.h"
#include "mission.h"
#include "coalition.h"

class CoalitionTreeModel : public QAbstractItemModel
{
public:
    CoalitionTreeModel(TMission m_mission);
    virtual ~CoalitionTreeModel();

    // QAbstractItemModel interface
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    void setupModelData(TMission mission, TreeItemBase *parent);


     TreeItemBase *rootItem;

     // QAbstractItemModel interface
public:
};

#endif // COALITIONTREEMODEL_H
