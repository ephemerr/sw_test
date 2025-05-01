#include "Map.hpp"
#include "Unit.hpp"

namespace sw::logic
{
    void Map::setCoords(uint32_t w, uint32_t h)
    {
        _width = w;
        _height = h;
    }

    Map::Map()
    {
    }

    void Map::moveUnit(uint32_t id, uint32_t x, uint32_t y)
    {
        if (!x || x > _width|| !y || y > _height) return;

        if (_units.count(id))
        {
            for (const auto &u : _units)
            {
                if (u.second.getX() == x && u.second.getY() == y)
                    return;
            }
           _units[id].setCoords(x,y);
        }
    }

    void Map::spawnUnit(Unit::Params params)
    {
       // _units[params.id] = Unit(params);
    }
}

