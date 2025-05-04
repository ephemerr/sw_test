#pragma once

#include "Attack.hpp"
#include "Unit.hpp"
#include "Coord.hpp"

#include "../EventLog.hpp" // TODO fix this dependence
                           //
#include <unordered_map>
#include <map>
#include <cstdint>
#include <functional>

namespace sw::logic {

	class Map
	{
    public:
        typedef std::unordered_map<uint32_t, Unit> UnitList;
        typedef std::function<void(uint32_t code, std::string)> ErrorHandler;
        typedef sw::EventLog EventHandler;
        typedef std::multimap<uint32_t, uint32_t> DistancesList;

        Map(EventHandler EventHandler, ErrorHandler errorHandler);
        void setCoords(uint32_t w, uint32_t h);
        void moveUnit(uint32_t id, uint32_t x, uint32_t y);
        void spawnUnit(const Unit::Params& params, const Unit::AttackParamsList& attacksParams);
        void startTheBattle();
        void doAttack(const Attack::Params& attack, uint32_t offender, uint32_t target);
        void doMarch(uint32_t offender, uint32_t target);
        DistancesList distancesToUnits(const Coord& from) const;
        uint32_t findTarget(const DistancesList& distances, const Attack::Params& attack) const;
        void reportError(uint32_t code, std::string msg);

        template<class TEvent>
        void reportEvent(TEvent&& event)
        {
            _eventHandler.log(_tick, std::forward<TEvent>(event));
        }

    private:
		uint32_t _width{};
		uint32_t _height{};
        uint64_t _tick;
        UnitList _units;
        ErrorHandler _errorHandler;
        EventHandler _eventHandler;

	};
}
