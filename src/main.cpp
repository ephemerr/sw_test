#include "Server.hpp"

#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
	using namespace sw;

	if (argc != 2)
	{
		throw std::runtime_error("Error: No file specified in command line argument");
	}

	std::ifstream file(argv[1]);
	if (!file)
	{
		throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
	}

    Server server;

    std::cout << "Reading setup from file" << std::endl;
    server.readSetupFile(file);

    std::cout << "Starting the simulation" << std::endl;
    server.run();

    std::cout << "Simulation ended" << std::endl;
}
