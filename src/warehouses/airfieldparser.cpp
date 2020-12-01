#include "airfieldparser.h"
#include "src/LuaConstants.h"
#include <QDebug>

using namespace luabridge;

AirfieldParser::AirfieldParser()
{

}

void AirfieldParser::ParseInto(TAirfield airfield, luabridge::LuaRef& ref)
{
    if(nullptr != airfield)
    {
        FuelReserve fuelReserve;
        fuelReserve.isUnlimited = ref[DCS_CST::unlimitedFuel].cast<bool>();
        fuelReserve.gasoline = ref[DCS_CST::gasoline][DCS_CST::InitFuel].cast<int>();
        fuelReserve.diesel= ref[DCS_CST::diesel][DCS_CST::InitFuel].cast<int>();
        fuelReserve.jet_fuel = ref[DCS_CST::jet_fuel][DCS_CST::InitFuel].cast<int>();
        airfield->setFuelReserve(fuelReserve);

        Inventory chopperInventory = parseAircraft(ref[DCS_CST::aircrafts][DCS_CST::helicopters]);
        chopperInventory.setIsUnlimited(ref[DCS_CST::unlimitedAircrafts].cast<bool>());
        airfield->setChoppersStock(chopperInventory);

        Inventory planeInventory = parseAircraft(ref[DCS_CST::aircrafts][DCS_CST::planes]);
        planeInventory.setIsUnlimited(ref[DCS_CST::unlimitedAircrafts].cast<bool>());
        airfield->setPlanesStock(planeInventory);
    }

}


void AirfieldParser::ParseAirfieldDataBase(const LuaRef& airfields)
{

}

Inventory AirfieldParser::parseAircraft(const LuaRef &aircraft)
{
    Inventory airframeStocks;
    if(!aircraft.isNil())
    {
        for(auto&& pair: pairs(aircraft))
        {
            InventoryItem airframes;
            airframes.itemCount = pair.second[DCS_CST::initialAmount].cast<int>();
            if(pair.first.isNumber())
            {
                qDebug() << pair.first.cast<int>();
            }
            else if (pair.first.isString())
            {
                airframes.itemName = QString::fromStdString(pair.first.cast<std::string>());
            }
            airframeStocks.addItem(airframes);
        }
    }
    return airframeStocks;
}
