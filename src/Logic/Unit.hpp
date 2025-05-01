#pragma once

#include "Attack.hpp"

#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>

namespace sw::logic
{
    class Unit {

    public:

        struct Params
        {
            uint32_t id{};
            uint32_t hp{};
            uint32_t speed{};
            std::vector<std::string> attacks{};
        };

        typedef std::unordered_map<std::string,Params> ParamTable;

        Unit();
        Unit(Params &params);
        void setCoords(uint32_t x, uint32_t y);
        uint32_t getX() const;
        uint32_t getY() const;

    private:
        uint32_t _x;
        uint32_t _y;
        Params _params;

        static ParamTable _paramTable;

    };
}
