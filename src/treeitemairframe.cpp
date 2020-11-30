#include "treeitemairframe.h"

TreeItemAirframe::TreeItemAirframe(
        TTYPE type,
        TAirframeStocks stocks,
        TreeItemBase *parentItem ):
TreeItemBase(parentItem),
m_stock{stocks},
m_type{type}
{

}

QVariant TreeItemAirframe::data(int column) const
{
    if(0 == column){
        if(m_type == TTYPE::CHOPPER) return QString("Chopper:");
        else return QString("Planes");
    }
    if(1 == column){
        return m_stock.count();
    }
}

int TreeItemAirframe::columnCount() const
{
    return 2;
}
