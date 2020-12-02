#ifndef MISSION_H
#define MISSION_H

#include <QSharedPointer>
#include <QString>
#include <QDate>
#include "coalition.h"

class Mission
{
public:
    Mission(const QString& theatreName);


    QString theatreName() const;


    QDate missionDate() const;
    void setMissionDate(const QDate &missionDate);


    Coalition& red() ;
    Coalition& blue() ;


private:
    const QString m_theatreName;
    QDate         m_missionDate;

    Coalition   m_red;
    Coalition   m_blue;
};

typedef QSharedPointer<Mission> TMission;

#endif // MISSION_H
