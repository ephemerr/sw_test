#pragma once

#include <cstdint>
#include <string>

namespace sw::logic
{
	struct UnitDied
	{
		constexpr static const char* Name = "UNIT_DIED";

		uint32_t unitId{};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
		}
	};
}
