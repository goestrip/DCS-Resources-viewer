#include "treeitembase.h"
#include "TreeItemVisitor.h"

TreeItemBase::TreeItemBase(TreeItemBase *parentItem):
    m_parentItem{parentItem}
{

}

TreeItemBase::~TreeItemBase()
{
    qDeleteAll(m_childItems);
}

void TreeItemBase::appendChild(TreeItemBase *child)
{
    m_childItems.append(child);
}

TreeItemBase *TreeItemBase::child(int row)
{
    if (row < 0 || row >= m_childItems.size())
        return nullptr;
    return m_childItems.at(row);
}

int TreeItemBase::childCount() const
{
    return m_childItems.count();
}

//int TreeItemBase::columnCount() const
//{
//    return 4;
//}

QVariant TreeItemBase::data(int column) const
{
    if(column == 0)
        return "root";

    else return QVariant::Invalid;
}

int TreeItemBase::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItemBase*>(this));

    return 0;
}

TreeItemBase *TreeItemBase::parentItem()
{
    return m_parentItem;
}

void TreeItemRoot::accept(TreeItemVisitor *visitor)
{
    //visitor->visit(this);
}
