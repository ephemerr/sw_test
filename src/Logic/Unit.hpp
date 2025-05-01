#pragma once

#include "Attack.hpp"
#include "Coord.hpp"

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
        static const Params& getDefaultParams(const std::string &str);

        typedef std::vector<Attack::Params> AttackParamsList;
        void setAttacks(const AttackParamsList &attacks);
        const AttackParamsList& getAttacks() const;

        void setCoords(const Coord& coords);
        const Coord& getCoord() const;

        Unit();
        Unit(const Params &params);

    private:
        Coord _coords;
        Params _params;
        std::vector<logic::Attack::Params> _attacksParams;
    };
}
