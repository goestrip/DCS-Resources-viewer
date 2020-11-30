#include "datamanager.h"
#include "warehouses/warehouseparser.h"
#include "mission/missionparser.h"

DataManager::DataManager()
{

}

bool DataManager::openMizFile(const QString &filePath)
{
    m_mizInterface = TMizInterface(new MizInterface(filePath)) ;


    warehouseFile = m_mizInterface->extractContent("warehouses");
    missionFile  = m_mizInterface->extractContent("mission");
    MissionParser missionParser;

    if(nullptr != missionFile)
    {
        m_mission = missionParser.Parse(missionFile->content());
    }
    if(nullptr != warehouseFile && nullptr != m_mission)
    {
        WarehouseParser warehouse;
        m_airfields = warehouse.Parse(warehouseFile->content(), m_mission->theatreName());
        return true;
    }
    else return false;

}

QString DataManager::getTheatre() const
{
    if(nullptr != m_mission)
    {
        return m_mission->theatreName();
    }
    return QString();
}

const TAirfields& DataManager::getAirfields()const
{
    return m_airfields;
}
