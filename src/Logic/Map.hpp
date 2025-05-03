#pragma once

#include "Attack.hpp"
#include "Unit.hpp"
#include "Coord.hpp"
#include "Events/Event.hpp"

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
        typedef std::function<void(uint64_t, logic::Event&)> EventHandler;
        EventHandler _eventHandler = nullptr;

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
        void setEventHandler(EventHandler handler);
        void reportEvent(uint64_t tic, logic::Event& event);
	};
}
