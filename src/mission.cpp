#include "mission.h"

Mission::Mission(const QString& theatreName):
    m_theatreName{theatreName.toLower()},
    m_red(Coalition::RED),
    m_blue(Coalition::BLUE)
{

}

QString Mission::theatreName() const
{
    return m_theatreName;
}

QDate Mission::missionDate() const
{
    return m_missionDate;
}

void Mission::setMissionDate(const QDate &missionDate)
{
    m_missionDate = missionDate;
}

Coalition& Mission::red()
{
    return m_red;
}


Coalition& Mission::blue()
{
    return m_blue;
}


