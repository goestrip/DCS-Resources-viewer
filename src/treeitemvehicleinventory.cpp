#include "treeitemvehicleinventory.h"

TreeItemVehicleInventory::TreeItemVehicleInventory(
        const QString& name,
        int count,
        TreeItemBase *parentItem ):
    TreeItemBase(parentItem),
    m_name{name},
    m_count{count}
{

}

int TreeItemVehicleInventory::columnCount() const
{
    return 2;
}

QVariant TreeItemVehicleInventory::data(int column) const
{
    if(0 == column) return m_name;
    else if(1 == column) return m_count;
    else return QVariant::Invalid;
}

void TreeItemVehicleInventory::accept(TreeItemVisitor *)
{

}
