#include "mission.h"

Mission::Mission(const QString& theatreName):
    m_theatreName{theatreName.toLower()}
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
