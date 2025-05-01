#include "Unit.hpp"
#include <cstdint>

namespace sw::logic {

    Unit::ParamTable Unit::_paramTable =
    {
        {"Swordsman",{1,100,1,{"SwordsmanMele"}}},
        {"Hunter",{2,100,1,{"HunterMele", "HunterRanged"}}},
    };

    Unit::Unit()
    {
    }

    Unit::Unit(Params &params): _params(params)
    {
    }

    void Unit::setCoords(uint32_t x, uint32_t y)
    {
        _x = x;
        _y = y;
    }

    uint32_t Unit::getX() const
    {
        return _x;
    }

    uint32_t Unit::getY() const
    {
        return _y;
    }

}
