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
            std::string type;
            uint32_t id{}; //TODO move id up to the class body
            uint32_t hp{};
            uint32_t speed{};
            std::vector<std::string> attacks{};
        };

        static const uint32_t UNIT_ID_INVALID = UINT32_MAX;

        typedef std::unordered_map<std::string,Params> ParamTable;
        static const Params& getDefaultParams(const std::string &str);

        typedef std::vector<Attack::Params> AttackParamsList;
        void setAttacks(const AttackParamsList &attacks);
        const AttackParamsList& getAttacks() const;

        void setCoords(const Coord& coords);
        const Coord& getCoord() const;

        uint32_t getId() const;
        uint32_t getHp() const;
        uint32_t getSpeed() const;

        Unit();
        Unit(const Params &params);

    private:
        Coord _coords;
        Params _params;
        std::vector<logic::Attack::Params> _attacksParams;
    };
}
