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
    lua_State* lua;
};

#endif // MISSIONPARSER_H
