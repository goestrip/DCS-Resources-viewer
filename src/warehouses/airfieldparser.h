#ifndef AIRFIELDPARSER_H
#define AIRFIELDPARSER_H

#include "lua.hpp"
#include "LuaBridge/LuaBridge.h"
#include "airfield.h"
#include "jsondbparser.h"

class AirfieldParser
{
public:
    AirfieldParser(const ObjectDBWrapper&  itemDbWrapper);
    void ParseInto(TAirfield airfield, luabridge::LuaRef& ref)const;
    //void ParseAirfieldDataBase(const luabridge::LuaRef& airfields)const;

private:
    Inventory parseAircraft(const luabridge::LuaRef& ref)const;
    Inventory parseEquipment(const luabridge::LuaRef& ref)const;

    const ObjectDBWrapper&  m_itemDbWrapper;
};

#endif // AIRFIELDPARSER_H
