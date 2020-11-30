#ifndef TREEITEMBASE_H
#define TREEITEMBASE_H

#include <QVector>
#include <QVariant>

class TreeItemBase
{
public:
    explicit TreeItemBase(TreeItemBase *parentItem = nullptr);
    //explicit TreeItem(const QVector<QVariant> &data, TreeItem *parentItem = nullptr);
    virtual ~TreeItemBase();

    void appendChild(TreeItemBase *child);

    TreeItemBase *child(int row);
    int childCount() const;
    virtual int columnCount() const ;
    virtual QVariant data(int column) const;
    int row() const;
    TreeItemBase *parentItem();

private:
    QVector<TreeItemBase*> m_childItems;
    //QVector<QVariant> m_itemData;
    TreeItemBase *m_parentItem;

    //QString m_name;
};

#endif // TREEITEMBASE_H
