#ifndef TREEITEMVISITOR_H
#define TREEITEMVISITOR_H

class TreeItemFuel;
class TreeItemAirfield;
class TreeItemBase;
class TreeItemAirframe;

class TreeItemVisitor{
public:

    virtual void visit(TreeItemFuel* item)=0;
    virtual void visit(TreeItemAirfield* item)=0;
    virtual void visit(TreeItemAirframe* item)=0;
};

#endif // TREEITEMVISITOR_H
