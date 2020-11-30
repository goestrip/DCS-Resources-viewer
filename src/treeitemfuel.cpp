#include "treeitemfuel.h"

TreeItemFuel::TreeItemFuel(FuelReserve fuelReserve,TreeItemBase *parentItem):
    TreeItemBase(parentItem),
    m_fuel{fuelReserve}
{

}

QVariant TreeItemFuel::data(int column) const
{
    if(0 == column){
        return QString("Fuel states:");
    }
    else if(1 == column){
        return QString("diesel: ") + QString::number(m_fuel.diesel);
    }
    if(2 == column){
        return QString("gasoline: ") + QString::number(m_fuel.gasoline);
    }
    if(3 == column){
        return QString("jet_fuel") + QString::number(m_fuel.jet_fuel);
    }
     else return QVariant::Invalid;
}

int TreeItemFuel::columnCount() const
{
    return 3;
}
