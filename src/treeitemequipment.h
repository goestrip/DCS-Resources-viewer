#ifndef TREEITEMEQUIPMENT_H
#define TREEITEMEQUIPMENT_H
#include "treeitembase.h"
#include "TreeItemVisitor.h"
#include "inventory.h"


class TreeItemEquipment: public TreeItemBase
{
public:
    TreeItemEquipment(const Inventory& stock,  TreeItemBase *parentItem = nullptr);

     int columnCount() const override;
     QVariant data(int column) const override;
     void accept(TreeItemVisitor *visitor) override;

     const Inventory *  getInventory()const;

private:
     const Inventory m_stock;

     // TreeItemBase interface

};

#endif // TREEITEMEQUIPMENT_H
