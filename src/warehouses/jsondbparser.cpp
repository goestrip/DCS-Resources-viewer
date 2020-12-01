#include "jsondbparser.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

JsonDbParser::JsonDbParser()
{

}

ObjectDBWrapper JsonDbParser::parse(const QByteArray& jsonContent)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonContent);
    dbItemList itemList;

    QJsonArray rootArray = jsonDoc.array();

    for(auto iter = rootArray.begin(); iter != rootArray.end(); iter++)
    {
        if(iter->isObject())
        {
            DbItem dbItem = readItem(iter->toObject());
            if(dbItem.getId() != 0)
            {
                itemList.insert(dbItem.getId(), dbItem);
            }
        }
    }

    return ObjectDBWrapper(itemList);
}

DbItem JsonDbParser::readItem(QJsonObject json)
{
    if(json.contains("name") && json.contains("id")){
        QString name = json.value("name").toString();
        int id = json.value("id").toInt();
        DbItem newItem(name, id);

        if(json.contains("children")&& json.value("children").isArray())
        {
            QJsonArray children = json.value("children").toArray();
            for(auto iter = children.begin(); iter != children.end(); iter++)
            {
                if(iter->isObject())
                {
                    DbItem dbItem = readItem(iter->toObject());
                    if(dbItem.getId() != 0)
                    {
                        newItem.addChildren(dbItem);
                        //itemList.insert(dbItem.getId(), dbItem);
                    }
                }
            }
        }

        if(json.contains("names"))
        {
            QJsonArray subNames = json.value("names").toArray();
            for(auto iter = subNames.begin(); iter != subNames.end(); iter++)
            {
                if(iter->isObject())
                {
                    QJsonObject object = iter->toObject();
                    if(object.contains("id")&&object.contains("name"))
                    {
                        newItem.addSubName(object.value("id").toInt(), object.value("name").toString());
                    }
                }
            }
        }


        return newItem;
    }
    return DbItem("",0);
}


DbItem::DbItem(const QString &name, int id):
    name{name},
    id{id}
{

}

void DbItem::addChildren(const DbItem &item)
{
    if(item.getId() != 0)
    {
        children.insert(item.getId(), item);
    }
}

bool DbItem::getChildren(int id, DbItem &child) const
{
    if(children.contains(id))
    {
        child = children.value(id);
        return true;
    }
    return false;
}

void DbItem::addSubName(int id, const QString &name)
{
    names.insert(id, name);
}

bool DbItem::getSubName(int id, QString &subName)
{
    if(names.contains(id))
    {
        subName = names.value(id);
        return true;
    }
    return false;
}


QString DbItem::getName() const
{
    return name;
}

int DbItem::getId() const
{
    return id;
}


ObjectDBWrapper::ObjectDBWrapper(dbItemList itemList):
    items{itemList}
{

}

QString ObjectDBWrapper::getNameForLevels(int level1, int level2, int level3, int level4) const
{
    QString  name;
    QTextStream out(&name);
    if(items.contains(level1))
    {
        DbItem item1 = items.value(level1);
        DbItem item2;
        if(item1.getChildren(level2, item2))
        {
            DbItem item3;
            if(item2.getChildren(level3, item3))
            {
                DbItem item4;
                QString subName;
                if(item3.getChildren(level4, item4))
                {
                    out << item4.getName();
                }
                else if(item3.getSubName(level4, subName) || item2.getSubName(level4, subName)) {
                    out << subName;
                }
                else out << item3.getName();
            }
            else out << item2.getName();
        }
        else out << item1.getName();
    }
    out<<" "<<level1<<"-"<<level2<<"-"<<level3<<"-"<<level4;
    return name;
}



