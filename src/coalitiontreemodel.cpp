#include "coalitiontreemodel.h"
#include "treeitemcoalition.h"

CoalitionTreeModel::CoalitionTreeModel(TMission   mission)
{
    rootItem = new TreeItemRoot();
    if(nullptr != mission)
    {
        setupModelData(mission, rootItem);
    }
}

CoalitionTreeModel::~CoalitionTreeModel()
{
    delete rootItem;
}

QModelIndex CoalitionTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItemBase *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItemBase*>(parent.internalPointer());

    TreeItemBase *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

QModelIndex CoalitionTreeModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    TreeItemBase *childItem = static_cast<TreeItemBase*>(child.internalPointer());
    TreeItemBase *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);}

int CoalitionTreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItemBase *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItemBase*>(parent.internalPointer());

    return parentItem->childCount();
}

int CoalitionTreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItemBase*>(parent.internalPointer())->columnCount();
    return rootItem->columnCount();
}

QVariant CoalitionTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItemBase *item = static_cast<TreeItemBase*>(index.internalPointer());

    return item->data(index.column());
}

void CoalitionTreeModel::setupModelData(TMission mission, TreeItemBase *parent)
{
    parent->appendChild(new treeItemCoalition(mission->blue(), parent));
    parent->appendChild(new treeItemCoalition(mission->red(), parent));
}


QVariant CoalitionTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if( 0 == section)return "type";
        else if(1 == section) return "count";
        else return QVariant::Invalid;
    }
    else return QAbstractItemModel::headerData(section, orientation, role);
}


