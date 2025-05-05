#include <catch2/catch_test_macros.hpp>

#include <vector>
#include <map>
#include <fstream>
#include <iostream>

// TODO redefine Server output interface to test it without breaking incapsulation
#define private public

#include "../../src/Logic/Map.hpp"
#include "../../src/EventLog.hpp"
#include "../../src/Server.hpp"

typedef std::map<std::string, uint32_t>  MessageData;

TEST_CASE( "Server test", "[server]" )
{
    sw::logic::Coord c0({0,0});
    sw::logic::Coord cX({8,0});
    sw::logic::Coord cY({9,9});
    REQUIRE(cY.distance(c0) == 9);
    REQUIRE(cY.distance(cX) == 9);

	std::ifstream file("../commands_example.txt");
	if (!file)
	{
		throw std::runtime_error("Error: File not found - " + std::string("commands_example.txt"));
	}
    sw::Server server;
    server.readSetupFile(file);

    auto& units = server.map._units;

    REQUIRE( units.size() == 3 );
    REQUIRE( server.map._width == 10 );
    REQUIRE( server.map._height == 10 );
    REQUIRE( units[3].getId() == 3 );
    REQUIRE( units[1].getId() == 1 );
    REQUIRE( units[2].getId() == 2 );
    REQUIRE( units[1]._coords.x == 9 );
    REQUIRE( units[1]._coords.y == 0 );
    REQUIRE( units[2]._coords.x == 0 );
    REQUIRE( units[2]._coords.y == 0 );
    REQUIRE( units[3]._coords.x == 9 );
    REQUIRE( units[3]._coords.y == 9 );
    REQUIRE( units[1]._hp == 5 );
    REQUIRE( units[1]._params.speed == 1 );
    REQUIRE( units[1]._attacksParams[0].strength == 2 );
    REQUIRE( units[1]._attacksParams[0].distance == 1 );
    REQUIRE( units[2]._hp == 10 );
    REQUIRE( units[2]._params.speed == 1 );
    REQUIRE( units[2]._attacksParams[0].strength == 5 );
    REQUIRE( units[2]._attacksParams[0].distance == 4 );
    REQUIRE( units[2]._attacksParams[1].strength == 1 );
    REQUIRE( units[2]._attacksParams[1].distance == 1 );
    REQUIRE( units[3]._hp == 10 );
    REQUIRE( units[3]._params.speed == 1 );
    REQUIRE( units[3]._attacksParams[0].strength == 2 );
    REQUIRE( units[3]._attacksParams[0].distance == 1 );

    auto distancies = server.map.distancesToUnits({0,0} );
    REQUIRE( distancies.size() == 2 );
    REQUIRE( distancies.count(9) == 2 );

    REQUIRE( server.map.findTarget(
                distancies, units[2]._attacksParams[0])
                    == sw::logic::Unit::UNIT_ID_INVALID);

    server.map.doMarch(1, 2);
    REQUIRE( units[1]._coords.x == 8 );
    REQUIRE( units[1]._coords.y == 0 );
    distancies = server.map.distancesToUnits({0,0} );
    REQUIRE( distancies.size() == 2);
    REQUIRE( distancies.count(9) == 1);
    REQUIRE( distancies.count(8) == 1);

    server.map.doIteration();
    REQUIRE( units[1]._coords.x == 7 );
    REQUIRE( units[1]._coords.y == 0 );
    distancies = server.map.distancesToUnits(units[2]._coords );
    REQUIRE( distancies.count(8) == 1);
    REQUIRE( distancies.count(6) == 1);

    server.map.doIteration();
    server.map.doMarch(1, 2);
    distancies = server.map.distancesToUnits(units[2]._coords );
    REQUIRE( distancies.count(7) == 1);
    REQUIRE( distancies.count(3) == 1);
    REQUIRE( server.map.findTarget( distancies, units[2]._attacksParams[0]) == 1 );
    server.map.doAttack(units[2]._attacksParams[0], 2, 1);
    REQUIRE( units.size() == 2 );
}



