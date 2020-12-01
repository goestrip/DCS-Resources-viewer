#ifndef TREEITEMAIRFRAME_H
#define TREEITEMAIRFRAME_H

#include "treeitembase.h"
#include "airfield.h"


class TreeItemAirframe : public TreeItemBase
{
public:
    enum class TTYPE{PLANE, CHOPPER};

    TreeItemAirframe(TTYPE type, const Inventory& stock, TreeItemBase *parentItem = nullptr);

    QVariant data(int column) const override;
    int columnCount() const override;
    void accept(TreeItemVisitor* visitor)override;

private:
    const Inventory m_stock;
    const TTYPE m_type;
};

#endif // TREEITEMAIRFRAME_H
