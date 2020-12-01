#include "treeitemairframe.h"
#include "TreeItemVisitor.h"

TreeItemAirframe::TreeItemAirframe(
        TTYPE type,
        const Inventory& stocks,
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
    else return QVariant::Invalid;
}

int TreeItemAirframe::columnCount() const
{
    return 2;
}

void TreeItemAirframe::accept(TreeItemVisitor *visitor)
{
     visitor->visit(this);
}
