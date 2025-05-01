#include "Unit.hpp"
#include "Attack.hpp"
#include <cstdint>

namespace sw::logic {


    const Unit::Params& Unit::getDefaultParams(const std::string &str)
    {
        static Unit::ParamTable _paramTable =
        {
            {"Swordsman",{1,100,1,{"SwordsmanMelee"}}},
            {"Hunter",{2,100,1,{"HunterMelee", "HunterRanged"}}},
        };

        return _paramTable[str];
    }

    Unit::Unit()
    {
    }

    Unit::Unit(const Params &params): _params(params)
    {
        for (const auto &attackName : _params.attacks)
        {
            auto attack = Attack::getDefaultParams(attackName);
           _attacksParams.push_back(attack);
        }
    }

    void Unit::setCoords(uint32_t x, uint32_t y)
    {
        _x = x;
        _y = y;
    }

    void Unit::setAttacks(const AttackParamsList &attacks)
    {
        _attacksParams = attacks;
    }

    const Unit::AttackParamsList& Unit::getAttacks()
    {
        return _attacksParams;
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
