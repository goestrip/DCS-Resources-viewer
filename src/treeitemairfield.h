#ifndef TREEITEMAIRFIELD_H
#define TREEITEMAIRFIELD_H

#include "treeitembase.h"
#include "warehouses/airfield.h"

class TreeItemAirfield : public TreeItemBase
{
public:
    TreeItemAirfield(TAirfield airfield, TreeItemBase *parentItem = nullptr);
    QVariant data(int column) const override;
    int columnCount() const override;

    void accept(TreeItemVisitor* visitor);

private:
    TAirfield   m_airfield;
};

#endif // TREEITEMAIRFIELD_H
