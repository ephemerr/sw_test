#include "Map.hpp"
#include "Attack.hpp"
#include "Unit.hpp"
#include "Coord.hpp"

#include <cstdint>
#include <vector>
#include <utility>

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
                const Coord& c = u.second.getCoord();
                if (c.x == x && c.y == y)
                    return;
            }
           _units[id].setCoords({x,y});
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
               auto distances = distancesToUnits(activeUnit.getCoord());
               for (const auto& attack: activeUnit.getAttacks())
               {

               }

               for (auto& target : _units) {

               }
           }
       }
    }
    //
    // void Map::doAttack(const Attack::Params& attack, uint32_t targer, uint32_t targer);
    //

    Map::DistancesList Map::distancesToUnits(const Coord& from) const
    {
        DistancesList res;
        for(const auto& [id,unit] : _units)
        {
            const Coord& target = unit.getCoord();
            auto distance = from.distance(target);
            res.insert(std::pair{distance,id});
        }
        return res;
    }

    Map::DistancesList Map::findOpenTargets(const Coord& from, const Attack::Params& attack) const
    {
        DistancesList res;
        for(const auto& [id,unit] : _units)
        {
            const Coord& target = unit.getCoord();
            auto distance = from.distance(target);
            if (attack.type | Attack::ATTACK_TYPE_RANGED && distance == 1)
            {
                return {};
            }
            if (distance > attack.distance || distance < attack.minDistance)
            {
                continue;
            }
        }
        return res;
    }
}

