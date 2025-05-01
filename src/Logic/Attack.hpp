#pragma once

#include <cstdint>
#include <unordered_map>
#include <string>

namespace sw::logic
{
	class Attack
    {
    public:

        struct Params
        {
            uint32_t id{};
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
