#ifndef AIRFIELD_H
#define AIRFIELD_H
#include <QString>
#include <QVector>
#include <QSharedPointer>
#include <QMap>

struct FuelReserve
{
    FuelReserve():gasoline{0},diesel{0}, jet_fuel{0}, isUnlimited{false}{};

    int gasoline;
    int diesel;
    int jet_fuel;
    bool isUnlimited;
};

struct AirframeStock
{
    AirframeStock():count{0}{};
    QString aicraftName;
    unsigned int count;
};
typedef QVector<AirframeStock> TAirframeStocks;


class Airfield
{
public:
    Airfield(int id, QString name);
    Airfield() = default;


    FuelReserve fuelReserve() const;
    void setFuelReserve(const FuelReserve &fuelReserve);
    void setPlanesStock(TAirframeStocks aircrafts);
    void setChoppersStock(TAirframeStocks aircrafts);

    QString name() const;
    int Id() const;

private:
    int m_Id;
    QString m_name;
    FuelReserve m_fuelReserve;
    TAirframeStocks m_choppers;
    TAirframeStocks m_planes;
};
typedef QSharedPointer<Airfield> TAirfield;
typedef QMap<int, TAirfield> TAirfields;
typedef QMap<QString, TAirfields> TAllMapAirfields;

#endif // AIRFIELD_H
