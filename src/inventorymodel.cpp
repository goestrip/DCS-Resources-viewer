#include "inventorymodel.h"
#include <QDebug>
InventoryModel::InventoryModel()
{
}



int InventoryModel::rowCount(const QModelIndex &parent) const
{
    int rows = m_inventory.getInventoryContent().count();
    return rows;

}

int InventoryModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant InventoryModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole)
    {
          const TInventoryItemList & itemList = m_inventory.getInventoryContent();
          int row = index.row();
          if(row >=0 && row < itemList.count())
        {
            if(index.column() == 0)
            {
                return itemList.at(row).itemName;
            }
            else if(index.column() == 1)
            {
                return itemList.at(row).itemCount;
            }
        }
        return index.row();
    }
    return QVariant::Invalid;
}

void InventoryModel::setCustomData(const Inventory &inventory)
{
    emit beginResetModel();
    qDebug()<< "set new inventory in model";
    m_inventory = inventory;
    emit endResetModel();
}


QVariant InventoryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Orientation::Horizontal && role == Qt::DisplayRole)
    {
        if(0 == section) return QString("model");
        else if(1 == section) return QString("quantity");
    }
    return QVariant::Invalid;
}





void InventoryModel::sort(int column, Qt::SortOrder order)
{
}
