#include "mission.h"

Mission::Mission(const QString& theatreName):
    m_theatreName{theatreName.toLower()}
{

}

QString Mission::theatreName() const
{
    return m_theatreName;
}
