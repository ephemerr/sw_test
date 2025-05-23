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
            uint32_t hp{};
            uint32_t speed{};
            std::vector<std::string> attacks{};
        };

        typedef std::unordered_map<std::string,Params> ParamTable;
        typedef std::vector<Attack::Params> AttackParamsList;

        static const uint32_t UNIT_ID_INVALID = UINT32_MAX;
        static const Params& getDefaultParams(const std::string &str);

        Unit();
        Unit(const Params &params, uint32_t id);
        void setAttacks(const AttackParamsList &attacks);
        const AttackParamsList& getAttacks() const;
        void setCoords(const Coord& coords);
        const Coord& getCoord() const;
        void setHp(uint32_t hp);
        uint32_t getHp() const;
        uint32_t getId() const;
        uint32_t getSpeed() const;

    private:
        Coord _coords;
        Params _params;
        uint32_t _hp;
        uint32_t _id;
        std::vector<logic::Attack::Params> _attacksParams;
    };
}
