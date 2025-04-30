#pragma once

#include "Unit.hpp"

#include <vector>
#include <cstdint>

namespace sw::logic
{
	struct Map
	{
		uint32_t width{};
		uint32_t height{};
        std::vector<Unit> units{};
	};
}
