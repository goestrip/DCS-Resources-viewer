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

void Airfield::setPlanesStock(TAirframeStocks aircrafts)
{
    m_planes = aircrafts;
}

void Airfield::setChoppersStock(TAirframeStocks aircrafts)
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

TAirframeStocks Airfield::choppers() const
{
    return m_choppers;
}

TAirframeStocks Airfield::planes() const
{
    return m_planes;
}
