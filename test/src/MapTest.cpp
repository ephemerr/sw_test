#include <catch2/catch_test_macros.hpp>

#include "../../src/Logic/Map.hpp"


TEST_CASE( "Map class test", "[map]" ) {
    sw::logic::Map map;
    map.setErrorHandler([] (std::string message)
            {
                std::cout << message << std::endl;
            });
    map.setCoords(10, 10);
    map.getCoord
}
