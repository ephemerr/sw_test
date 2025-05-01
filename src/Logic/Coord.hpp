#pragma once

#include <cstdint>

namespace sw::logic {

    struct Coord
    {
        uint32_t x;
        uint32_t y;

        uint32_t distance(const Coord& target) const;
    };
}
