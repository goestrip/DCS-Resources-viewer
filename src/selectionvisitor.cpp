#include "selectionvisitor.h"
#include <QDebug>
#include "treeitemairframe.h"
#include "treeitemequipment.h"

SelectionVisitor::SelectionVisitor():
    m_inventory{nullptr}
{

}


void SelectionVisitor::visit(TreeItemFuel *item)
{
    qDebug()<<"visit fuel item";
}

void SelectionVisitor::visit(TreeItemAirfield *item)
{
    qDebug()<<"visit airfield item";
}

void SelectionVisitor::visit(TreeItemAirframe *item)
{
       qDebug()<<"visit aircraft item";
       m_inventory = item->getInventory();
}

const Inventory *SelectionVisitor::getInventory()
{
    return m_inventory;
}


void SelectionVisitor::visit(TreeItemEquipment *item)
{
    m_inventory = item->getInventory();
}
