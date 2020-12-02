#include "airfieldparser.h"
#include "src/LuaConstants.h"
#include <QDebug>
#include <QException>

using namespace luabridge;

AirfieldParser::AirfieldParser(const ObjectDBWrapper&  itemDbWrapper):
    m_itemDbWrapper{itemDbWrapper}
{

}

void AirfieldParser::ParseInto(TAirfield airfield, luabridge::LuaRef& ref)const
{
    if(nullptr != airfield)
    {
        try {
            FuelReserve fuelReserve;
            if(!ref[DCS_CST::unlimitedFuel].isNil())    fuelReserve.isUnlimited = ref[DCS_CST::unlimitedFuel].cast<bool>();
            if(!ref[DCS_CST::gasoline].isNil())         fuelReserve.gasoline = ref[DCS_CST::gasoline][DCS_CST::InitFuel].cast<int>();
            if(!ref[DCS_CST::diesel].isNil())           fuelReserve.diesel= ref[DCS_CST::diesel][DCS_CST::InitFuel].cast<int>();
            if(!ref[DCS_CST::jet_fuel].isNil())         fuelReserve.jet_fuel = ref[DCS_CST::jet_fuel][DCS_CST::InitFuel].cast<int>();
            airfield->setFuelReserve(fuelReserve);

            if(!ref[DCS_CST::aircrafts].isNil())
            {
                Inventory chopperInventory = parseAircraft(ref[DCS_CST::aircrafts][DCS_CST::helicopters]);
                chopperInventory.setIsUnlimited(ref[DCS_CST::unlimitedAircrafts].cast<bool>());
                airfield->setChoppersStock(chopperInventory);
                Inventory planeInventory = parseAircraft(ref[DCS_CST::aircrafts][DCS_CST::planes]);
                planeInventory.setIsUnlimited(ref[DCS_CST::unlimitedAircrafts].cast<bool>());
                airfield->setPlanesStock(planeInventory);
            }
            if(!ref[DCS_CST::weapons].isNil())
            {
                Inventory equipment = parseEquipment(ref[DCS_CST::weapons]);
                equipment.setIsUnlimited(ref[DCS_CST::unlimitedMunitions].cast<bool>());
                airfield->setEquipmentStock(equipment);
            }
        }  catch (QException ex) {
            qCritical()<<ex.what();
        }
    }

}



Inventory AirfieldParser::parseAircraft(const LuaRef &aircraft)const
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

Inventory AirfieldParser::parseEquipment(const LuaRef &ref)const
{
    Inventory equimentStock;
    if(!ref.isNil())
    {
        for(auto&& pair: pairs(ref))
        {
            InventoryItem equipment;
            equipment.itemCount = pair.second[DCS_CST::initialAmount].cast<int>();
            LuaRef wsType = pair.second[DCS_CST::wsType];
            if(!wsType.isNil())
            {
                int level1 = wsType[1].cast<int>();
                int level2 = wsType[2].cast<int>();
                int level3 = wsType[3].cast<int>();
                int level4 = wsType[4].cast<int>();
                equipment.itemName = m_itemDbWrapper.getNameForLevels(level1, level2, level3, level4);
            }

            equimentStock.addItem(equipment);
        }
    }
    return equimentStock;
}








