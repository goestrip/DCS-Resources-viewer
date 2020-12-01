#ifndef JSONDBPARSER_H
#define JSONDBPARSER_H
#include <QMap>

class QJsonObject;

class DbItem{
public:
    DbItem() = default;
    DbItem(const QString& name, int id);
    void addChildren(const DbItem& item);
    bool getChildren(int id, DbItem& child)const;

    void addSubName(int id, const QString& subName);
    bool getSubName(int id, QString& subName);

    QString getName() const;
    int getId() const;
    //QMap<int, DbItem> getChildren() const;

private:
    QString   name;
    int       id;
    QMap<int, DbItem> children;
    QMap<int, QString> names;
};
typedef QMap<int, DbItem> dbItemList ;



class ObjectDBWrapper{
public :
    ObjectDBWrapper(dbItemList);

    QString getNameForLevels(int level1, int level2, int level3, int level4)const;

private:
    const dbItemList  items;
};



class JsonDbParser
{
public:
    JsonDbParser();
    ObjectDBWrapper parse(const QByteArray& jsonContent);

private:
    DbItem readItem(QJsonObject json);

};

#endif // JSONDBPARSER_H
