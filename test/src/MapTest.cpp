#include <catch2/catch_test_macros.hpp>

#include "../../src/Logic/Map.hpp"
#include "../../src/EventLog.hpp"

#include <vector>
#include <map>

typedef std::map<std::string, uint32_t>  MessageData;

class MapTestEventVisitor
{
public:

    MessageData data;

    template <typename T>
    void visit(const char* name, const T& value)
    {
        data[name] = value;
    }
};

class MapEventQueue : public sw::EventLog
{
public:
    std::vector<MessageData> dataQueue;

    template <class TEvent>
    void log(uint64_t tick, TEvent&& event)
    {
        MapTestEventVisitor visitor;
        event.visit(visitor);
        std::cout << "HEY" << std::endl;
    }
};

TEST_CASE( "Map class test", "[map]" ) {
    MapEventQueue eventHandler;

    sw::logic::Map map;
    map.init(eventHandler,
            [] (uint32_t code, std::string message)
            {
                std::cout << message << std::endl;
            });

    map.setCoords(10, 10);

    REQUIRE( eventHandler.dataQueue.size() == 1 );
}
