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
    void sort(int column, Qt::SortOrder order) override;

    void setCustomData(const Inventory& inventory);

private:
    Inventory   m_inventory;

    // QAbstractItemModel interface
public:

    // QAbstractItemModel interface
public:
};

#endif // INVENTORYMODEL_H
