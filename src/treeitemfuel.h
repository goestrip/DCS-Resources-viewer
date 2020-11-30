#ifndef TREEITEMFUEL_H
#define TREEITEMFUEL_H

#include "treeitembase.h"
#include "warehouses/airfield.h"

class TreeItemFuel : public TreeItemBase
{
public:
    TreeItemFuel(FuelReserve fuelReserve,TreeItemBase *parentItem = nullptr);
    QVariant data(int column) const override;
    int columnCount() const override;

    void accept(TreeItemVisitor* visitor)override;
private:
    const FuelReserve m_fuel;
};

#endif // TREEITEMFUEL_H
