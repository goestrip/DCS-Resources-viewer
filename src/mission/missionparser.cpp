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
    m_mission.clear();

    QByteArray fileData = luaContent.toLocal8Bit();
    int read_result = luaL_dostring(lua, fileData.data());
    qDebug()<<"MissionParser lua read content "<< " : "<< ((read_result == LUA_OK)?"ok":"ko");

    luaL_openlibs(lua);
    lua_pcall(lua, 0, 0, 0);

    LuaRef luaMission = getGlobal(lua, DCS_CST::mission.c_str());
    if(!luaMission.isNil())
    {
        parseTheatre(luaMission);
        parseDate(luaMission);
        parseCoalitions(luaMission);
    }
    else{
        qWarning()<<"no mission node found in the mission lua file";
    }

    return m_mission;
}

void MissionParser::parseTheatre(LuaRef& luaMission)
{
    LuaRef  theatre = luaMission[DCS_CST::theatre.c_str()];
    if(!theatre.isNil() && theatre.isString())
    {
        QString theathreName = QString::fromStdString(theatre.cast<std::string>());
        m_mission = TMission(new Mission(theathreName));
    }
}

void MissionParser::parseDate(LuaRef& luaMission)
{
    LuaRef luaDate = luaMission[DCS_CST::date.c_str()];
    if(!luaDate.isNil())
    {
        int year = luaDate[DCS_CST::Year.c_str()].cast<int>();
        int month= luaDate[DCS_CST::Month.c_str()].cast<int>();
        int day = luaDate[DCS_CST::Day.c_str()].cast<int>();

        m_mission->setMissionDate(QDate(year, month, day));
        qDebug()<<"mission date is :"<<m_mission->missionDate();
    }
}

void MissionParser::parseCoalitions(LuaRef& luaMission)
{
    LuaRef luaCoalitions = luaMission[DCS_CST::coalition.c_str()];
    if(!luaCoalitions.isNil() && nullptr != m_mission)
    {
        if(!luaCoalitions[DCS_CST::blue].isNil())
        {
            parseOneCoalition(luaCoalitions[DCS_CST::blue], m_mission->blue());
        }
        if(!luaCoalitions[DCS_CST::red].isNil())
        {
            Coalition coalition(Coalition::RED);
            parseOneCoalition(luaCoalitions[DCS_CST::red], m_mission->red());
        }
    }

}

void MissionParser::parseOneCoalition(LuaRef luaCoalition, Coalition &coalition)
{
    if(!luaCoalition[DCS_CST::country].isNil())
    {
        for(auto&& pair : pairs(luaCoalition[DCS_CST::country]))
        {
            parseVehicles(pair.second, coalition);
        }
    }
}

//void MissionParser::parseHelicopters(LuaRef& luaCountry)
//{

//}

//void MissionParser::parsePlanes(LuaRef& luaMission)
//{

//}

void MissionParser::parseVehicles(LuaRef& luaCountry, Coalition &coalition)
{
    VehicleInventory groundVehicles;
    if(!luaCountry.isNil()
            && !luaCountry[DCS_CST::vehicle].isNil()
            && !luaCountry[DCS_CST::vehicle][DCS_CST::group].isNil())
    {
        for(auto&& pair : pairs(luaCountry[DCS_CST::vehicle][DCS_CST::group]))
        {
            if(!pair.second[DCS_CST::type].isNil() && pair.second[DCS_CST::type].isString())
            {
                QString unitType = QString::fromStdString(pair.second[DCS_CST::type].tostring());
                coalition.addVehicle(Coalition::GROUND, unitType);
            }
        }
    }
}





