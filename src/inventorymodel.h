#ifndef INVENTORYMODEL_H
#define INVENTORYMODEL_H

#include <QAbstractTableModel>
#include "inventory.h"

class InventoryModel : public QAbstractTableModel
{
public:
    InventoryModel();

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void setCustomData(const Inventory& inventory);

private:
    Inventory   m_inventory;


};

#endif // INVENTORYMODEL_H
