#include "airfieldtreemodel.h"
#include "treeitemairfield.h"

AirfieldTreeModel::AirfieldTreeModel(const TAirfields& airfieldData,  QObject *parent):
 QAbstractItemModel(parent)
{
    rootItem = new TreeItemBase();
    setupModelData(airfieldData, rootItem);
}

AirfieldTreeModel::~AirfieldTreeModel()
{
    delete rootItem;
}


QModelIndex AirfieldTreeModel::index(int row, int column, const QModelIndex &parent) const
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

QModelIndex AirfieldTreeModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    TreeItemBase *childItem = static_cast<TreeItemBase*>(child.internalPointer());
    TreeItemBase *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int AirfieldTreeModel::rowCount(const QModelIndex &parent) const
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

int AirfieldTreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItemBase*>(parent.internalPointer())->columnCount();
    return rootItem->columnCount();
}

QVariant AirfieldTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItemBase *item = static_cast<TreeItemBase*>(index.internalPointer());

    return item->data(index.column());
}

void AirfieldTreeModel::setupModelData(const TAirfields &airfieldData, TreeItemBase *parent)
{
    for(TAirfields::const_iterator airfield = airfieldData.begin(); airfield != airfieldData.end(); airfield++)
    {
        parent->appendChild(new TreeItemAirfield(*airfield, parent));
    }
}
