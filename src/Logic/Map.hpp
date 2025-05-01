#pragma once

#include "Unit.hpp"

#include <unordered_map>
#include <cstdint>

namespace sw::logic
{
	class Map
	{
		uint32_t _width{};
		uint32_t _height{};
        std::unordered_map<uint32_t, Unit> _units;

    public:
        Map();
        void setCoords(uint32_t w, uint32_t h);
        void moveUnit(uint32_t id, uint32_t x, uint32_t y);
        void spawnUnit(Unit::Params params);
	};
}
