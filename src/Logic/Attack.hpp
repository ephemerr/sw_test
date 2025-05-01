#pragma once

#include <cstdint>
#include <unordered_map>
#include <string>

namespace sw::logic
{
	class Attack
    {
    public:
        enum Type {
             ATTACK_TYPE_NONE   = 0
            ,ATTACK_TYPE_MELEE  = 1
            ,ATTACK_TYPE_RANGED = 2
            ,ATTACK_TYPE_FIRE   = 4
        };

        struct Params
        {
            uint32_t type{};
            uint32_t distance{};
            uint32_t minDistance{};
            uint32_t radius{};
            uint32_t strength{};
        };

        typedef std::unordered_map<std::string,Params> ParamTable;
        static const Params& getDefaultParams(const std::string &str);

    private:
        Params _params;
    };
}
