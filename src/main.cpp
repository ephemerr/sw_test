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

#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
	using namespace sw;

	EventLog eventLog;

	if (argc != 2)
	{
		throw std::runtime_error("Error: No file specified in command line argument");
	}

	std::ifstream file(argv[1]);
	if (!file)
	{
		throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
	}

	// Code for example...

    logic::Map map;

	std::cout << "Commands:\n";

	io::CommandParser parser;
	parser.add<io::CreateMap>([&map, &eventLog](auto command)
    {
        printDebug(std::cout, command);
        map.setCoords(command.width, command.height);
	    eventLog.log(1, logic::MapCreated{{}, command.width, command.height});
    })
    .add<io::SpawnSwordsman>([&map, &eventLog](auto command)
    {
        printDebug(std::cout, command);
        auto u = logic::Unit::getDefaultParams("Swordsman");
        u.id = command.unitId;
        u.hp = command.hp;
        auto a1 = logic::Attack::getDefaultParams("Melee");
        a1.strength = command.strength;
        logic::Unit::AttackParamsList attacksParams = {a1};
        map.spawnUnit(u, attacksParams);
        map.moveUnit(u.id, command.x, command.y);
        eventLog.log(0, logic::UnitSpawned{u.id, "Swordsman", command.x, command.y});
    })
    .add<io::SpawnHunter>([&map, &eventLog](auto command)
    {
        printDebug(std::cout, command);
        logic::Unit::Params u = logic::Unit::getDefaultParams("Hunter");
        u.id = command.unitId;
        u.hp = command.hp;
        auto a1 = logic::Attack::getDefaultParams("Ranged");
        a1.strength = command.agility;
        a1.distance = command.range;
        auto a2 = logic::Attack::getDefaultParams("Melee");
        a2.strength = command.strength;
        logic::Unit::AttackParamsList attacksParams = {a1, a2};
        map.spawnUnit(u, attacksParams);
        map.moveUnit(u.id, command.x, command.y);
        eventLog.log(1, logic::UnitSpawned{u.id, "Hunter", command.x, command.y});
    })
	.add<io::March>([&map, &eventLog](auto command)
    {
        printDebug(std::cout, command);
	    eventLog.log(1, logic::UnitMoved{command.unitId, command.targetX, command.targetY});
        map.moveUnit(command.unitId, command.targetX, command.targetY);
    });

	parser.parse(file);

	// return 0;

	// eventLog.log(1, logic::MapCreated{{}, 10, 10});
	// eventLog.log(1, logic::UnitSpawned{1, "Swordsman", 0, 0});
	// eventLog.log(1, logic::UnitSpawned{2, "Hunter", 9, 0});
	// eventLog.log(1, logic::MarchStarted{1, 0, 0, 9, 0});
	// eventLog.log(1, logic::MarchStarted{2, 9, 0, 0, 0});
	// eventLog.log(1, logic::UnitSpawned{3, "Swordsman", 0, 9});
	// eventLog.log(1, logic::MarchStarted{3, 0, 9, 0, 0});
    //
	// eventLog.log(2, logic::UnitMoved{1, 1, 0});
	// eventLog.log(2, logic::UnitMoved{2, 8, 0});
	// eventLog.log(2, logic::UnitMoved{3, 0, 8});
    //
	// eventLog.log(3, logic::UnitMoved{1, 2, 0});
	// eventLog.log(3, logic::UnitMoved{2, 7, 0});
	// eventLog.log(3, logic::UnitMoved{3, 0, 7});
    //
	// eventLog.log(4, logic::UnitMoved{1, 3, 0});
	// eventLog.log(4, logic::UnitAttacked{2, 1, 5, 0});
	// eventLog.log(4, logic::UnitDied{1});
	// eventLog.log(4, logic::UnitMoved{3, 0, 6});
    //
	// eventLog.log(5, logic::UnitMoved{2, 6, 0});
	// eventLog.log(5, logic::UnitMoved{3, 0, 5});
    //
	// eventLog.log(6, logic::UnitMoved{2, 5, 0});
	// eventLog.log(6, logic::UnitMoved{3, 0, 4});
    //
	// eventLog.log(7, logic::UnitAttacked{2, 3, 5, 5});
	// eventLog.log(7, logic::UnitMoved{3, 0, 3});
    //
	// eventLog.log(8, logic::UnitAttacked{2, 3, 5, 0});
	// eventLog.log(8, logic::UnitDied{3});
}
