#pragma once

#include "Attack.hpp"
#include "Unit.hpp"
#include "Coord.hpp"
#include "Events/Event.hpp"
#include "Events/UnitMoved.hpp"
#include "Events/UnitSpawned.hpp"

#include "../EventLog.hpp" // TODO fix this dependence

#include <unordered_map>
#include <map>
#include <cstdint>
#include <functional>

namespace sw::logic {

	class Map
	{
		uint32_t _width{};
		uint32_t _height{};
        std::unordered_map<uint32_t, Unit> _units;
        EventLog _logger;
        uint64_t _tick;

    public:
        Map();
        void setCoords(uint32_t w, uint32_t h);
        void moveUnit(uint32_t id, uint32_t x, uint32_t y);
        void spawnUnit(const Unit::Params& params, const Unit::AttackParamsList& attacksParams);
        void startTheBattle();
        void doAttack(const Attack::Params& attack, uint32_t offender, uint32_t target);
        void doMarch(uint32_t offender, uint32_t target);
        typedef std::multimap<uint32_t, uint32_t> DistancesList;
        DistancesList distancesToUnits(const Coord& from) const;
        uint32_t findTarget(const DistancesList& distances, const Attack::Params& attack) const;

        template<class TEvent>
        void reportEvent(TEvent&& event)
        {
            _logger.log(_tick, std::forward<TEvent>(event));
        }
	};
}
