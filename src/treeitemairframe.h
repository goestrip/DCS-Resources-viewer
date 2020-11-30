#ifndef TREEITEMAIRFRAME_H
#define TREEITEMAIRFRAME_H

#include "treeitembase.h"
#include "warehouses/airfield.h"

class TreeItemAirframe : public TreeItemBase
{
public:
    enum class TTYPE{PLANE, CHOPPER};

    TreeItemAirframe(TTYPE type, TAirframeStocks stock, TreeItemBase *parentItem = nullptr);

    QVariant data(int column) const override;
    int columnCount() const override;
private:
    const TAirframeStocks m_stock;
    const TTYPE m_type;
};

#endif // TREEITEMAIRFRAME_H
