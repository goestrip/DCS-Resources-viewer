#include "missionparser.h"
#include <QDebug>
#include "LuaConstants.h"
#include <QDate>

using namespace luabridge;

MissionParser::MissionParser()
{
    lua = luaL_newstate() ;
    if(nullptr != lua)
    {
        qDebug()<<"MissionParser : open lua context";
    }
    else {
        qCritical() << "MissionParser : can not open lua context";
    }
}

MissionParser::~MissionParser()
{
    if(lua != nullptr) lua_close(lua);
}

TMission MissionParser::Parse(QString luaContent)
{
    TMission mission;

    QByteArray fileData = luaContent.toLocal8Bit();
    int read_result = luaL_dostring(lua, fileData.data());
    qDebug()<<"MissionParser lua read content "<< " : "<< ((read_result == LUA_OK)?"ok":"ko");

    luaL_openlibs(lua);
    lua_pcall(lua, 0, 0, 0);

    LuaRef luaMission = getGlobal(lua, DCS_CST::mission.c_str());
    if(!luaMission.isNil())
    {
        LuaRef  theatre = luaMission[DCS_CST::theatre.c_str()];
        if(!theatre.isNil() && theatre.isString())
        {
            QString theathreName = QString::fromStdString(theatre.cast<std::string>());
            mission = TMission(new Mission(theathreName));
        }
        LuaRef luaDate = luaMission[DCS_CST::date.c_str()];
        if(!luaDate.isNil())
        {
            int year = luaDate[DCS_CST::Year.c_str()].cast<int>();
            int month= luaDate[DCS_CST::Month.c_str()].cast<int>();
            int day = luaDate[DCS_CST::Day.c_str()].cast<int>();

            mission->setMissionDate(QDate(year, month, day));
            qDebug()<<"mission date is :"<<mission->missionDate();
        }
    }
    else{
        qWarning()<<"no mission node found in the mission lua file";
    }

    return mission;
}
