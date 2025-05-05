#include "Coord.hpp"


namespace sw::logic {

    uint32_t Coord::distance(const Coord& target) const
    {
        auto maxX = this->x > target.x ? this->x : target.x;
        auto maxY = this->y > target.y ? this->y : target.y;
        auto minX = this->x < target.x ? this->x : target.x;
        auto minY = this->y < target.y ? this->y : target.y;
        auto dX = maxX - minX;
        auto dY = maxY - minY;
        auto maxD = dX > dY ? dX : dY;
        return maxD;
    }

    bool Coord::operator==(const Coord& rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
}
