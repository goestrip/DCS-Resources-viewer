#include "airfield.h"

Airfield::Airfield(int id, QString name):
    m_Id(id),
    m_name(name)
{

}

FuelReserve Airfield::fuelReserve() const
{
    return m_fuelReserve;
}

void Airfield::setFuelReserve(const FuelReserve &fuelReserve)
{
    m_fuelReserve = fuelReserve;
}

void Airfield::setPlanesStock(const Inventory& aircrafts)
{
    m_planes = aircrafts;
}

void Airfield::setChoppersStock(const Inventory& aircrafts)
{
    m_choppers = aircrafts;
}


QString Airfield::name() const
{
    return m_name;
}

int Airfield::Id() const
{
    return m_Id;
}

const Inventory& Airfield::choppers() const
{
    return m_choppers;
}

const Inventory& Airfield::planes() const
{
    return m_planes;
}
