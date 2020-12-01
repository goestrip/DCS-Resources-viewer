#ifndef MISSION_H
#define MISSION_H

#include <QSharedPointer>
#include <QString>
#include <QDate>

class Mission
{
public:
    Mission(const QString& theatreName);


    QString theatreName() const;


    QDate missionDate() const;
    void setMissionDate(const QDate &missionDate);

private:
    const QString m_theatreName;
    QDate         m_missionDate;
};

typedef QSharedPointer<Mission> TMission;

#endif // MISSION_H
