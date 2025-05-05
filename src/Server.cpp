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
                    std::cout << msg;
                });

        parser.add<io::CreateMap>([this](auto command)
        {
            map.setCoords(command.width, command.height);
            eventLog.log(1, logic::MapCreated{command.width, command.height});
        })
        .add<io::SpawnSwordsman>([this](auto command)
        {
            auto unitParams = logic::Unit::getDefaultParams("Swordsman");
            unitParams.hp = command.hp;
            auto attackParams = logic::Attack::getDefaultParams("Melee");
            attackParams.strength = command.strength;
            logic::Unit::AttackParamsList attacksParams = {attackParams};
            map.spawnUnit(unitParams, attacksParams, command.unitId);
            map.moveUnit(command.unitId, {command.x, command.y});
            eventLog.log(1, logic::UnitSpawned{command.unitId, "Swordsman", command.x, command.y});
        })
        .add<io::SpawnHunter>([this](auto command)
        {
            auto unitParams = logic::Unit::getDefaultParams("Hunter");
            unitParams.hp = command.hp;
            auto attackParams = logic::Attack::getDefaultParams("Ranged");
            attackParams.strength = command.agility;
            attackParams.distance = command.range;
            auto attackParams2 = logic::Attack::getDefaultParams("Melee");
            attackParams2.strength = command.strength;
            logic::Unit::AttackParamsList attacksParams = {attackParams, attackParams2};
            map.spawnUnit(unitParams, attacksParams, command.unitId);
            map.moveUnit(command.unitId, {command.x, command.y});
            eventLog.log(1, logic::UnitSpawned{command.unitId, "Hunter", command.x, command.y});
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
