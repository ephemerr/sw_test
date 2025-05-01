#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/Events/MapCreated.hpp>
#include <IO/Events/MarchEnded.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <IO/Events/UnitDied.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/System/CommandParser.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/System/PrintDebug.hpp>

#include "Logic/Attack.hpp"
#include "Logic/Map.hpp"
#include "Logic/Unit.hpp"

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
	parser.add<io::CreateMap>([&map](auto command)
    {
        printDebug(std::cout, command);
        map.setCoords(command.width,command.height);
    })
    .add<io::SpawnSwordsman>([&map](auto command)
    {
        printDebug(std::cout, command);
        auto u = logic::Unit::getDefaultParams("Swordsman"); // TODO DRY
        u.id = command.unitId;
        u.hp = command.hp;
        auto a1 = logic::Attack::getDefaultParams("SwordsmanMelee");
        a1.strength = command.strength;
        std::vector<logic::Attack::Params> attacksParams = {a1};
        auto &unit = map.spawnUnit(u);
        unit.setAttacks(attacksParams);
        map.moveUnit(u.id, command.x, command.y);
    })
    .add<io::SpawnHunter>([&map](auto command)
    {
        printDebug(std::cout, command);
        logic::Unit::Params u = logic::Unit::getDefaultParams("Hunter"); // TODO: DRY
        u.id = command.unitId;
        u.hp = command.hp;
        auto a1 = logic::Attack::getDefaultParams("HunterRanged");
        a1.strength = command.agility;
        auto a2 = logic::Attack::getDefaultParams("HunterMelee");
        a1.strength = command.strength;
        std::vector<logic::Attack::Params> attacksParams = {a1, a2};
        auto &unit = map.spawnUnit(u);
        unit.setAttacks(attacksParams);
        map.moveUnit(u.id, command.x, command.y);
    })
	.add<io::March>([&map](auto command)
    {
        printDebug(std::cout, command);
        map.moveUnit(command.unitId, command.targetX, command.targetY);
    });

	parser.parse(file);

	return 0;
}
