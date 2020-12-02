#include "coalition.h"

Coalition::Coalition(SIDE side):
    m_coalition{side}
{

}

Coalition::SIDE Coalition::coalition() const
{
    return m_coalition;
}

void Coalition::addVehicle(Coalition::VEHICLE_TYPE type, const QString &typeName)
{
    if(VEHICLE_TYPE::GROUND == type)
    {
        groundVehicles.insert(typeName, groundVehicles.value(typeName, 0) + 1);
    }
}
