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

        airfield->setChoppersStock(parseAircraft(ref[DCS_CST::aircrafts][DCS_CST::helicopters]));
        airfield->setPlanesStock(parseAircraft(ref[DCS_CST::aircrafts][DCS_CST::planes]));
    }

}


void AirfieldParser::ParseAirfieldDataBase(const LuaRef& airfields)
{

}

TAirframeStocks AirfieldParser::parseAircraft(const LuaRef &aircraft)
{
    TAirframeStocks airframeStocks;
    if(!aircraft.isNil())
    {
        for(auto&& pair: pairs(aircraft))
        {
            AirframeStock airframes;
            airframes.count = pair.second[DCS_CST::initialAmount].cast<int>();
            if(pair.first.isNumber())
            {
                qDebug() << pair.first.cast<int>();
            }
            else if (pair.first.isString())
            {
                airframes.aicraftName = QString::fromStdString(pair.first.cast<std::string>());
            }
            airframeStocks.push_back(airframes);
        }
    }
    return airframeStocks;
}
