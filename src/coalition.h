#ifndef COALITION_H
#define COALITION_H

#include <QMap>

typedef QMap<QString, int>VehicleInventory;

class Coalition
{
public:
    enum SIDE{RED, BLUE, NEUTRAL};
    enum VEHICLE_TYPE{PLANE, CHOPPER, GROUND};

    Coalition(SIDE side);

    SIDE coalition() const;
    void addVehicle(VEHICLE_TYPE type, const QString& typeName);



private:
    const SIDE  m_coalition;

    VehicleInventory    groundVehicles;
};

#endif // COALITION_H
