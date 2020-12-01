#include "treeitemairfield.h"
#include "treeitemfuel.h"
#include "treeitemairframe.h"
#include "TreeItemVisitor.h"
#include "treeitemequipment.h"

TreeItemAirfield::TreeItemAirfield(TAirfield airfield, TreeItemBase *parentItem):
    TreeItemBase(parentItem),
    m_airfield(airfield)
{
    if(nullptr != airfield)
    {
        appendChild(new TreeItemFuel(airfield->fuelReserve(), this));
        appendChild(new TreeItemAirframe(TreeItemAirframe::TTYPE::CHOPPER, airfield->choppers(), this));
        appendChild(new TreeItemAirframe(TreeItemAirframe::TTYPE::PLANE ,airfield->planes(), this));
        appendChild(new TreeItemEquipment(airfield->equipment(), this));
    }
}

QVariant TreeItemAirfield::data(int column) const
{
    if(0 == column){
        return m_airfield->name();
    }
    if(1 == column){
        if(m_airfield->fuelReserve().isUnlimited)
        {
            return QString("fuel: ") + QChar(0x221E);
        }
        else return QString("fuel: ")
                + QString::number(m_airfield->fuelReserve().getTotal())
                +QString("t");
    }
    if(2 == column){
        if(m_airfield->choppers().isUnlimited()){
            return QString("choppers: ") + QChar(0x221E);
        }
        else{
            return QString("choppers: ") + QString::number(m_airfield->choppers().count());
        }
    }
    if(3 == column){
        if(m_airfield->planes().isUnlimited()){
            return QString("planes: ") + QChar(0x221E);
        }
        else{
            return QString("planes: ") + QString::number(m_airfield->planes().count());
        }

    }
    else return QVariant::Invalid;
}

int TreeItemAirfield::columnCount() const
{
    return 4;
}

void TreeItemAirfield::accept(TreeItemVisitor *visitor)
{
    visitor->visit(this);
}
