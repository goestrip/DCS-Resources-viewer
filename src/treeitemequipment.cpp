#include "treeitemequipment.h"

TreeItemEquipment::TreeItemEquipment(const Inventory& stock,
                                     TreeItemBase *parentItem):
    TreeItemBase(parentItem),
    m_stock{stock}
{

}


int TreeItemEquipment::columnCount() const
{
     return 2;
}

QVariant TreeItemEquipment::data(int column) const
{
    if(0 == column){
        return QString("equipment");
    }
    else if(1 == column)
    {
        return m_stock.count();
    }

    else return QVariant::Invalid;
}

void TreeItemEquipment::accept(TreeItemVisitor *visitor)
{
      visitor->visit(this);
}

const Inventory * TreeItemEquipment::getInventory() const
{
   return &m_stock ;
}

