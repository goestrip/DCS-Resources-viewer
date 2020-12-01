#ifndef INVENTORY_H
#define INVENTORY_H
#include <QString>
#include <QVector>

struct InventoryItem
{
    InventoryItem():itemCount{0}{};
    QString itemName;
    unsigned int itemCount;
};
typedef QVector<InventoryItem> TInventoryItemList;


class Inventory
{
public:
    Inventory();

    unsigned int count()const;

    const TInventoryItemList& getInventoryContent()const;

    bool isUnlimited() const;
    void setIsUnlimited(bool value);
    void addItem(const InventoryItem& item);

private:
    bool m_isUnlimitemd;
    TInventoryItemList m_items;
    unsigned int m_itemCount;
};

#endif // INVENTORY_H
