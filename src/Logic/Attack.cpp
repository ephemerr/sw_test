#include "Attack.hpp"


namespace sw::logic
{
    const Attack::Params& Attack::getDefaultParams(const std::string &str)
    {
        static Attack::ParamTable _paramTable =
        {
            {"SwordsmanMelee",{1,1,1,0,50}},
            {"HunterRanged",{2,0,2,0,75}},
            {"HunterMelee",{3,1,1,0,25}}
        };
        return _paramTable[str];
    }
}
