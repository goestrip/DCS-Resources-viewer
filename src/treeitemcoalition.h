#ifndef TREEITEMCOALITION_H
#define TREEITEMCOALITION_H

#include "treeitembase.h"
#include "coalition.h"

class treeItemCoalition : public TreeItemBase
{
public:
    treeItemCoalition(const Coalition& coalition, TreeItemBase *parentItem = nullptr);

    int columnCount() const override;
    QVariant data(int column) const override;
    void accept(TreeItemVisitor *visitor) override;

private:
    const Coalition&    m_coalition;

};

#endif // TREEITEMCOALITION_H
