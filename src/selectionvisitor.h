#ifndef SELECTIONVISITOR_H
#define SELECTIONVISITOR_H

#include "TreeItemVisitor.h"
class Inventory;

class SelectionVisitor : public TreeItemVisitor
{
public:
    SelectionVisitor();

    // TreeItemVisitor interface
public:
    void visit(TreeItemFuel *item) override;
    void visit(TreeItemAirfield *item) override;
    void visit(TreeItemAirframe *item) override;
    void visit(TreeItemEquipment *item) override;

    Inventory const* getInventory();
private:
    Inventory const* m_inventory;

    // TreeItemVisitor interface

};

#endif // SELECTIONVISITOR_H
