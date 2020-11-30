#ifndef TREEITEMBASE_H
#define TREEITEMBASE_H

#include <QVector>
#include <QVariant>
class TreeItemVisitor;

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

    virtual void accept(TreeItemVisitor* visitor) = 0;

private:
    QVector<TreeItemBase*> m_childItems;
    //QVector<QVariant> m_itemData;
    TreeItemBase *m_parentItem;

    //QString m_name;
};

class TreeItemRoot : public TreeItemBase
{
    public:
    virtual void accept(TreeItemVisitor* visitor) override;
};

#endif // TREEITEMBASE_H
