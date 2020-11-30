#ifndef WAREHOUSEPARSER_H
#define WAREHOUSEPARSER_H

#include <QString>
#include "lua.hpp"
#include "LuaBridge/LuaBridge.h"
#include "airfield.h"


class WarehouseParser
{
public:
    WarehouseParser();
    virtual ~WarehouseParser();

    TAirfields Parse(QString luaContent, const QString& mapName);

private:
    TAllMapAirfields loadAirfields();

    lua_State* lua;
};

#endif // WAREHOUSEPARSER_H
