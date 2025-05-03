#pragma once

#include "Event.hpp"

#include <cstdint>

namespace sw::logic
{
	struct MapCreated : public Event
	{
		constexpr static const char* Name = "MAP_CREATED";

		uint32_t width{};
		uint32_t height{};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("width", width);
			visitor.visit("height", height);
		}
	};
}
