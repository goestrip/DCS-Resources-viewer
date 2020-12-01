#include "warehouseparser.h"
#include <QDebug>
#include <QFile>

#include "LuaConstants.h"
#include "airfieldparser.h"

using namespace luabridge;

WarehouseParser::WarehouseParser()
{
    lua = luaL_newstate() ;
    if(nullptr != lua)
    {
        qDebug()<<"WarehouseParser : open lua context";
    }
    else {
        qCritical() << "WarehouseParser : can not open lua context";
    }
}

WarehouseParser::~WarehouseParser()
{
    qDebug()<<"close lua context";
    if(lua != nullptr) lua_close(lua);
}

TAirfields WarehouseParser::Parse(QString luaContent, const QString& mapName)
{
    TAllMapAirfields maps = loadAirfields();
    ObjectDBWrapper dbWrapper = loadDbItem();

    AirfieldParser airfieldParser(dbWrapper);

    TAirfields selectedMap;
    if(!maps.contains(mapName)){
        qWarning() << "map "<< mapName<< " not found in the library";
    }
    else{
        selectedMap = maps.value(mapName);
    }


    QByteArray fileData = luaContent.toLocal8Bit();
    int read_result = luaL_dostring(lua, fileData.data());
    //auto read_result = luaL_dofile(lua, filePath.data());
    qDebug()<<"lua read content "<< " : "<< ((read_result == LUA_OK)?"ok":"ko");

    luaL_openlibs(lua);
    lua_pcall(lua, 0, 0, 0);
    LuaRef warehouse = getGlobal(lua, DCS_CST::warehouses.c_str());
    if (!warehouse.isNil()) {
        LuaRef airports = warehouse[DCS_CST::airports.c_str()];
        if(!airports.isNil()){

            for(auto&& pair: pairs(airports))
            {
                LuaRef luaAirfield = pair.second;
                if(!luaAirfield.isNil())
                {
                    if(selectedMap.contains(pair.first))
                    {
                        TAirfield airfield = selectedMap.value(pair.first);
                        airfieldParser.ParseInto(airfield, luaAirfield);
                    }

                }
            }
        }
        else {
            qWarning()<< "airport node not found";
        }
    }
    else{
        qWarning()<< "warehouse variable not found";
    }

    return selectedMap;
}

TAllMapAirfields WarehouseParser::loadAirfields()
{
    TAllMapAirfields allMapsAirfield;

    QFile file("://resources/airfield_names.lua");
    if(file.open( QIODevice::ReadOnly))
    {
        QByteArray fileData = file.readAll();
        file.close();

        int read_result = luaL_dostring(lua, fileData.data());
        qDebug()<<"lua read airfield : "<<file.fileName() << " : "<< ((read_result == LUA_OK)?"ok":"ko");

        LuaRef airfield = getGlobal(lua, "Airfields");
        if(!airfield.isNil() )
        {
            for(auto&& pair: pairs(airfield))
            {
                QString mapName = QString::fromStdString(pair.first.cast<std::string>()).toLower();
                TAirfields airfields;
                for(auto&& airfield: pairs(airfield[pair.first]))
                {
                    qDebug()<<"\t["<< airfield.first.cast<int>()<<"]="  <<QString::fromStdString(airfield.second.cast<std::string>());
                    const int airfieldId = airfield.first.cast<int>();
                    QString airfieldName =  QString::fromStdString(airfield.second.cast<std::string>());
                    TAirfield newAirfield(new Airfield(airfieldId, airfieldName));
                    airfields.insert(airfieldId, newAirfield);

                }
                allMapsAirfield.insert(mapName, airfields);
            }
        }
    }
    else{
        qWarning()<<"can't open file syria";
    }
    return allMapsAirfield;
}


ObjectDBWrapper WarehouseParser::loadDbItem()
{
    JsonDbParser dbParser;
    QFile jsonDbFile(":/resources/object_db.json");
    if(jsonDbFile.open(QIODevice::ReadOnly))
    {
        return dbParser.parse(jsonDbFile.readAll());
    }
}

