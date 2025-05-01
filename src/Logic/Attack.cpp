#include "Attack.hpp"


namespace sw::logic
{
    const Attack::Params& Attack::getDefaultParams(const std::string &str)
    {
        static Attack::ParamTable _paramTable =
        {
            {"Melee", {ATTACK_TYPE_MELEE,1,1,0,50}},
            {"Ranged",   {ATTACK_TYPE_RANGED,UINT32_MAX,2,0,75}},
        };
        return _paramTable[str];
    }
}
