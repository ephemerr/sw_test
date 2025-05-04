#pragma once

#include "IO/Commands/CreateMap.hpp"
#include "IO/Commands/March.hpp"
#include "IO/Commands/SpawnHunter.hpp"
#include "IO/Commands/SpawnSwordsman.hpp"
#include "IO/System/CommandParser.hpp"
#include "IO/System/PrintDebug.hpp"

#include "Logic/Events/Events.hpp"
#include "Logic/Attack.hpp"
#include "Logic/Map.hpp"
#include "Logic/Unit.hpp"

#include "EventLog.hpp"

namespace sw
{
    class Server
    {
    public:

        Server();
        void readSetupFile(std::istream& stream);
        void run();

    private:

	    EventLog eventLog;
        logic::Map map;
	    io::CommandParser parser;

    };
}
