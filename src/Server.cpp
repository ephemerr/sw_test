#include "Server.hpp"

#include "IO/Commands/CreateMap.hpp"
#include "IO/Commands/March.hpp"
#include "IO/Commands/SpawnHunter.hpp"
#include "IO/Commands/SpawnSwordsman.hpp"
#include "IO/System/PrintDebug.hpp"

#include "Logic/Attack.hpp"
#include "Logic/Unit.hpp"
#include "Logic/Events/Events.hpp"

namespace sw
{
    Server::Server()
    {
        map.init( eventLog,
           [] (uint64_t code, std::string msg)
                {
                    // printDebug(std::cout, msg);
                });

        parser.add<io::CreateMap>([this](auto command)
        {
            map.setCoords(command.width, command.height);
            eventLog.log(1, logic::MapCreated{command.width, command.height});
        })
        .add<io::SpawnSwordsman>([this](auto command)
        {
            auto u = logic::Unit::getDefaultParams("Swordsman");
            u.id = command.unitId;
            u.hp = command.hp;
            auto a1 = logic::Attack::getDefaultParams("Melee");
            a1.strength = command.strength;
            logic::Unit::AttackParamsList attacksParams = {a1};
            map.spawnUnit(u, attacksParams);
            map.moveUnit(u.id, {command.x, command.y});
            eventLog.log(0, logic::UnitSpawned{u.id, "Swordsman", command.x, command.y});
        })
        .add<io::SpawnHunter>([this](auto command)
        {
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
            map.moveUnit(u.id, {command.x, command.y});
            eventLog.log(1, logic::UnitSpawned{u.id, "Hunter", command.x, command.y});
        })
        .add<io::March>([this](auto command)
        {
            eventLog.log(1, logic::UnitMoved{command.unitId, command.targetX, command.targetY});
            map.moveUnit(command.unitId, {command.targetX, command.targetY});
        });
    }

    void Server::readSetupFile(std::istream& stream)
    {
	    parser.parse(stream);
    }

    void Server::run()
    {
        map.startTheBattle();
    }
}
