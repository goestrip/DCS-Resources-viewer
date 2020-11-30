#ifndef MISSION_H
#define MISSION_H

#include <QSharedPointer>
#include <QString>

class Mission
{
public:
    Mission(const QString& theatreName);


    QString theatreName() const;

private:
    const QString m_theatreName;
};

typedef QSharedPointer<Mission> TMission;

#endif // MISSION_H
