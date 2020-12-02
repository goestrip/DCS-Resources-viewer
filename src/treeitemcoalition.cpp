#include "treeitemcoalition.h"
#include "treeitemvehicleinventory.h"

treeItemCoalition::treeItemCoalition(const Coalition& coalition, TreeItemBase *parentItem ):
    TreeItemBase(parentItem),
    m_coalition{coalition}
{
    const VehicleInventory& map = m_coalition.getGroundVehicles();
    for(VehicleInventory::const_iterator iter = map.begin(); iter != map.end(); iter ++)
    {
        appendChild(new TreeItemVehicleInventory(iter.key(), iter.value(), this));
    }
}


int treeItemCoalition::columnCount() const
{
    return 2;
}

QVariant treeItemCoalition::data(int column) const
{
    if(0 == column)
    {
        if(m_coalition.coalition() == Coalition::BLUE)
        {
            return QString("Blue");
        }
        else if(m_coalition.coalition() == Coalition::RED)
        {
            return QString("Red");
        }
        else return QVariant::Invalid;
    }
    else{
        return QVariant::Invalid;
    }
}

void treeItemCoalition::accept(TreeItemVisitor *)
{
}
