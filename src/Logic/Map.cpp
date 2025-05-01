#include "Map.hpp"
#include "Attack.hpp"
#include "Unit.hpp"

namespace sw::logic
{
    Map::Map()
    {
    }

    void Map::setCoords(uint32_t w, uint32_t h)
    {
        _width = w;
        _height = h;
    }

    void Map::moveUnit(uint32_t id, uint32_t x, uint32_t y)
    {
        if (!x || x > _width|| !y || y > _height) return;

        if (_units.count(id))
        {
            for (const auto &u : _units)
            {
                if (u.second.getX() == x && u.second.getY() == y)
                    return;
            }
           _units[id].setCoords(x,y);
        }
    }

    void Map::spawnUnit(const Unit::Params& params, const Unit::AttackParamsList& attacksParams = {})
    {
       _units[params.id] = Unit(params);
       _units[params.id].setAttacks(attacksParams);
    }

    void Map::startTheBattle()
    {
       while(_units.size() > 1)
       {
           for (auto &[id, activeUnit]: _units)
           {
               const auto& attacksList = activeUnit.getAttacks();
               for (auto &attack: attacksList)
               {
               }

               for (auto &target : _units) {

               }
           }
       }
    }
}

