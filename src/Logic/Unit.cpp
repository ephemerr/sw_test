#include "Unit.hpp"
#include "Attack.hpp"

#include <cstdint>

namespace sw::logic {

    const Unit::Params& Unit::getDefaultParams(const std::string &str)
    {
        static Unit::ParamTable _paramTable =
        {
            {"Swordsman", {"Swordsman",100,1,{"Melee"}}},
            {"Hunter",    {"Hunter",100,1,{"Ranged", "Melee"}}},
        };

        return _paramTable[str];
    }

    Unit::Unit()
    {
    }

    Unit::Unit(const Params &params, uint32_t id)
        : _params(params), _id(id)
    {
        for (const auto &attackName : _params.attacks)
        {
            auto attack = Attack::getDefaultParams(attackName);
           _attacksParams.push_back(attack);
        }
        _hp = params.hp;
    }

    void Unit::setAttacks(const AttackParamsList &attacks)
    {
        _attacksParams = attacks;
    }

    const Unit::AttackParamsList& Unit::getAttacks() const
    {
        return _attacksParams;
    }

    void Unit::setCoords(const Coord& coords)
    {
        _coords = coords;
    }

    const Coord& Unit::getCoord() const
    {
        return _coords;
    }

    uint32_t Unit::getId() const
    {
        return _id;
    }

    uint32_t Unit::getHp() const
    {
        return _hp;
    }

    void Unit::setHp(uint32_t hp)
    {
        _hp = hp;
    }

    uint32_t Unit::getSpeed() const
    {
        return _params.speed;
    }

}
