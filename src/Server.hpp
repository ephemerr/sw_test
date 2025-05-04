#pragma once

#include "IO/System/CommandParser.hpp"
#include "Logic/Map.hpp"
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
