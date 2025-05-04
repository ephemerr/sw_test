#pragma once

#include "IO/System/details/PrintFieldVisitor.hpp"
#include <iostream>
#include <typeindex>
#include <unordered_map>

namespace sw
{
	class EventLog
	{
	public:
		void log(uint64_t tick, auto event)
		{
			std::cout << "[" << tick << "] " << event.Name << " ";
			PrintFieldVisitor visitor(std::cout);
			event.visit(visitor);
			std::cout << std::endl;
		}
	};
}
