#ifndef TREEITEMVEHICLEINVENTORY_H
#define TREEITEMVEHICLEINVENTORY_H

#include "treeitembase.h"

class TreeItemVehicleInventory : public TreeItemBase
{
public:
    TreeItemVehicleInventory(const QString& name, int count, TreeItemBase *parentItem = nullptr);

    int columnCount() const override;
    QVariant data(int column) const override;
    void accept(TreeItemVisitor *visitor) override;

private:
    const QString m_name;
    const int     m_count;
};

#endif // TREEITEMVEHICLEINVENTORY_H
