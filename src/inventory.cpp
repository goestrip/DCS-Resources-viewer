#include "inventory.h"

Inventory::Inventory():
    m_itemCount{0}
{

}

bool Inventory::isUnlimited() const
{
    return m_isUnlimitemd;
}

void Inventory::setIsUnlimited(bool value)
{
    m_isUnlimitemd = value;
}

void Inventory::addItem(const InventoryItem &item)
{
    m_itemCount += item.itemCount;
    m_items.push_back(item);
}


unsigned int Inventory::count()const
{
    return m_itemCount;
}
