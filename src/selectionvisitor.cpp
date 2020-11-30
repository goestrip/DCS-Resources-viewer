#include "selectionvisitor.h"
#include <QDebug>

SelectionVisitor::SelectionVisitor()
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
}
