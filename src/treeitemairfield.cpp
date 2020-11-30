#include "treeitemairfield.h"
#include "treeitemfuel.h"
#include "treeitemairframe.h"

TreeItemAirfield::TreeItemAirfield(TAirfield airfield, TreeItemBase *parentItem):
    TreeItemBase(parentItem),
    m_airfield(airfield)
{
    if(nullptr != airfield)
    {
        appendChild(new TreeItemFuel(airfield->fuelReserve(), this));
        appendChild(new TreeItemAirframe(TreeItemAirframe::TTYPE::CHOPPER, airfield->choppers(), this));
        appendChild(new TreeItemAirframe(TreeItemAirframe::TTYPE::PLANE ,airfield->planes(), this));
    }
}

QVariant TreeItemAirfield::data(int column) const
{
    if(0 == column){
        return m_airfield->name();
    }
    if(1 == column){
        return QString("fuel: ")
                + QString::number(m_airfield->fuelReserve().getTotal())
                +QString("t");
    }
    if(2 == column){
        return QString("choppers: ") + QString::number(m_airfield->choppers().count());
    }
    if(3 == column){
        return QString("planes: ") + QString::number( m_airfield->planes().count());
    }
    else return QVariant::Invalid;
}

int TreeItemAirfield::columnCount() const
{
   return 4;
}
