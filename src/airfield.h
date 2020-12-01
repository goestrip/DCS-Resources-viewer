#ifndef AIRFIELD_H
#define AIRFIELD_H
#include <QString>
#include <QVector>
#include <QSharedPointer>
#include <QMap>

#include "inventory.h"

struct FuelReserve
{
    FuelReserve():gasoline{0},diesel{0}, jet_fuel{0}, isUnlimited{false}{};
    int getTotal(){return gasoline + diesel + jet_fuel;}
    int gasoline;
    int diesel;
    int jet_fuel;
    bool isUnlimited;
};

class Airfield
{
public:
    Airfield(int id, QString name);
    Airfield() = default;


    FuelReserve fuelReserve() const;
    void setFuelReserve(const FuelReserve &fuelReserve);
    void setPlanesStock(const Inventory& aircrafts);
    void setChoppersStock(const Inventory& aircrafts);
    void setEquipmentStock(const Inventory& equipment);

    QString name() const;
    int Id() const;

    const Inventory& choppers() const;
    const Inventory& planes() const;
    const Inventory& equipment() const;

private:
    int m_Id;
    QString m_name;
    FuelReserve m_fuelReserve;
    Inventory m_choppers;
    Inventory m_planes;
    Inventory m_equipments;

};
typedef QSharedPointer<Airfield> TAirfield;
typedef QMap<int, TAirfield> TAirfields;
typedef QMap<QString, TAirfields> TAllMapAirfields;

#endif // AIRFIELD_H
