#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "mizinterface.h"
#include "airfield.h"
#include "mission.h"

class DataManager
{
public:
    DataManager();

    bool openMizFile(const QString& filePath);

    QString getTheatre()const;
    const TAirfields& getAirfields()const;
    QDate   getMissionDate()const;

    TMission getMission() const;

private:
    TMizInterface   m_mizInterface;

    TMizContentFile warehouseFile;
    TMizContentFile missionFile;

    TMission m_mission;
    TAirfields m_airfields;
};

#endif // DATAMANAGER_H
