#include "Map.hpp"
#include "Attack.hpp"

#include "Unit.hpp"
#include "Coord.hpp"
#include "Events/Events.hpp"

#include <vector>
#include <cstdint>
#include <iterator>
#include <utility>
#include <iterator>
#include <random>
#include <format>

namespace sw::logic
{
    Map::Map()
    {
    }

    void Map::init(Map::EventHandler eventHandler, Map::ErrorHandler errorHandler)
    {
        _eventHandler = eventHandler;
        _errorHandler = errorHandler;
        _tick = 1;
    }

    void Map::setCoords(uint32_t w, uint32_t h)
    {
        _width = w;
        _height = h;
    }

    void Map::moveUnit(uint32_t id, const Coord& to)
    {
        if (!to.x || to.x > _width|| !to.y || to.y > _height)
        {
            return;
        }

        if (_units.count(id))
        {
            for (const auto &u : _units)
            {
                const Coord& c = u.second.getCoord();
                if (c.x == to.x && c.y == to.y)
                {
                    reportError(std::format("There is already unit at {} {}", to.x, to.y));
                    return;
                }
            }
           _units[id].setCoords({to.x, to.y});
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
            if (_tick > 1000) break;

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

    void Map::doAttack(const Attack::Params& attack, uint32_t offenderId, uint32_t targetId)
    {
        auto& offender = _units[offenderId];
        auto& target = _units[targetId];
        auto hp = target.getHp();

        hp = (attack.strength > hp) ? 0 : hp - attack.strength;

        reportEvent(UnitAttacked{offenderId, targetId, attack.strength, hp});

        if (hp)
        {
            target.setHp(hp);
        }
        else
        {
            _units.erase(targetId);
            reportEvent(UnitDied{targetId});
        }
    }

    void Map::doMarch(uint32_t unitId, uint32_t targetId)
    {
        // TODO it's just a dummy algorithm - needs rewriting
        const Coord& target = _units[targetId].getCoord();
        const Coord& from = _units[unitId].getCoord();
        Coord closest = from;
        uint32_t minDist = from.distance(target);
        const auto speed = _units[unitId].getSpeed();

        reportEvent(MarchStarted{unitId, from.x, from.y, target.x, target.y});

        for (uint32_t x=0; x<_width; x++)
        {
            for (uint32_t y=0; y<_width; y++)
            {
                const Coord xy{x, y};
                if (from.distance(xy) > speed || isOccupied(xy))
                {
                    continue;
                }
                auto dist = xy.distance(target);
                if (dist < minDist)
                {
                    closest = xy;
                    minDist = dist;
                }
            }
        }
        if (closest != from)
        {
           moveUnit(unitId, closest);
        }
        reportEvent(MarchEnded{unitId, target.x, target.y});
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

    void Map::reportError(std::string msg)
    {
        _errorHandler(0, msg);
    }

    bool Map::isOccupied(const Coord& coords) const
    {
        for (const auto& [id, u] : _units)
        {
            if (coords == u.getCoord())
            {
                return true;
            }
        }
        return false;
    }
}

