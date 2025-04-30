#pragma once

#include <cstdint>

namespace sw::logic
{
	struct Attack
	{
        uint32_t distance{};
        uint32_t minDistance{};
        uint32_t radius{};
        uint32_t type{};
        uint32_t strenght{};
	};
}
