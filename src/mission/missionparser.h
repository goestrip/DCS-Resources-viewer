#ifndef MISSIONPARSER_H
#define MISSIONPARSER_H

#include <QString>
#include "lua.hpp"
#include "LuaBridge/LuaBridge.h"

#include "Mission.h"

class MissionParser
{
public:
    MissionParser();
    virtual ~MissionParser();

    TMission Parse(QString luaContent);
private:
    void parseTheatre(luabridge::LuaRef& luaMission);
    void parseDate(luabridge::LuaRef& luaMission);
    void parseCoalitions(luabridge::LuaRef& luaMission);
    void parseOneCoalition(luabridge::LuaRef luaCoalition, Coalition& coalition);
//    void parseHelicopters(luabridge::LuaRef& luaCountry);
//    void parsePlanes(luabridge::LuaRef& luaMission);
    void parseVehicles(luabridge::LuaRef& luaCountry, Coalition &coalition);

    TMission    m_mission;
    lua_State* lua;
};

#endif // MISSIONPARSER_H
