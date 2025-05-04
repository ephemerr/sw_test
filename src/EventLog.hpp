#pragma once

#include "IO/System/details/PrintFieldVisitor.hpp"
#include <iostream>
#include <cstdint>

namespace sw
{
	class EventLog
	{
	public:
        template<class TEvent>
		void log(uint64_t tick, TEvent&& event)
		{
			std::cout << "[" << tick << "] " << event.Name << " ";
			PrintFieldVisitor visitor(std::cout);
			event.visit(visitor);
			std::cout << std::endl;
		}
	};
}
