#ifndef SELECTIONVISITOR_H
#define SELECTIONVISITOR_H

#include "TreeItemVisitor.h"

class SelectionVisitor : public TreeItemVisitor
{
public:
    SelectionVisitor();

    // TreeItemVisitor interface
public:
    void visit(TreeItemFuel *item) override;
    void visit(TreeItemAirfield *item) override;
    void visit(TreeItemAirframe *item) override;

    // TreeItemVisitor interface
public:
};

#endif // SELECTIONVISITOR_H
