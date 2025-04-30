#pragma once

#include "Attack.hpp"

#include <cstdint>
#include <vector>

namespace sw::logic
{
	struct Unit
	{
		uint32_t id{};
		uint32_t hp{};
        std::vector<Attack> attacks{};
	};
}
