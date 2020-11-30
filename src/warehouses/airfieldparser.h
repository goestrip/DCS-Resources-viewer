#ifndef AIRFIELDPARSER_H
#define AIRFIELDPARSER_H

#include "lua.hpp"
#include "LuaBridge/LuaBridge.h"
#include "airfield.h"

class AirfieldParser
{
public:
    AirfieldParser();
    static void ParseInto(TAirfield airfield, luabridge::LuaRef& ref);
    static void ParseAirfieldDataBase(const luabridge::LuaRef& airfields);

private:
    static TAirframeStocks parseAircraft(const luabridge::LuaRef& ref);

};

#endif // AIRFIELDPARSER_H
