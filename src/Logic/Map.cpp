#include "Map.hpp"
#include "Attack.hpp"

#include "Unit.hpp"
#include "Coord.hpp"

#include <vector>
#include <cstdint>
#include <iterator>
#include <utility>
#include <iterator>
#include <random>

namespace sw::logic
{
    Map::Map()
    {
        _tick = 0;
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
           _units[id].setCoords({x, y});
            reportEvent(UnitMoved{id, x, y});
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
            _tick++;

            for (auto &[id, activeUnit]: _units)
            {
                auto distances = distancesToUnits(activeUnit.getCoord());
                if (!distances.size())
                {
                   //TODO error messages
                   return;
                }
                bool attackComplete = false;
                for (const auto& attack: activeUnit.getAttacks())
                {
                    auto targetId = findTarget(distances, attack);
                    if (targetId == Unit::UNIT_ID_INVALID)
                    {
                        break;
                    }
                    doAttack(attack, activeUnit.getId(), targetId);
                    attackComplete = true;
                    break;
                }
                if (!attackComplete)
                {
                    // TODO smart choice of march target
                    auto moveTarget = distances.begin()->second;
                    doMarch(activeUnit.getId(), moveTarget);
                }
            }
        }
    }

    void Map::doAttack(const Attack::Params& attack, uint32_t offender, uint32_t target)
    {

    }

    void Map::doMarch(uint32_t offender, uint32_t target) {

    }

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

    uint32_t Map::findTarget(const DistancesList& distances, const Attack::Params& attack) const
    {
        uint32_t res = Unit::UNIT_ID_INVALID;
        const auto& maxDist = std::prev(distances.end())->first;
        const auto& minDist = distances.begin()->first;
        std::random_device rd;
        std::mt19937 gen(rd());

        std::vector<uint32_t> targetUnits;

        if (attack.type | Attack::ATTACK_TYPE_RANGED
               && minDist == 1) return res;
        for (int i=minDist; i<=maxDist; i++)
        {
            if (i < attack.minDistance) continue;
            if (i > attack.distance) break;

            auto targets = distances.equal_range(i);
            for (auto& it = targets.first; it != targets.second; it = std::next(it))
            {   // TODO make it by std algorithm
                targetUnits.push_back(it->second);
            }
            std::uniform_int_distribution<> distr(0, targetUnits.size()-1);
            res = distr(gen);
            break;
        }
        return res;
    }
}

