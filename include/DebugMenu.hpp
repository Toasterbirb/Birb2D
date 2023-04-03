#pragma once

#include "BaseEntity.hpp"
#include "Rect.hpp"
#include "ResourceMonitor.hpp"
#include "Timestep.hpp"
#include <vector>

namespace Birb
{
	struct EntityInfo
	{
		EntityInfo();
		std::string* 	name;
		Rect* 			rect;
		float* 			angle;
		bool deleted;
	};

	struct DebugMenu
	{
		static int AddEntity(BaseEntity& entity);

		static void EntityMenu();
		static void ResouceMonitor(const Diagnostics::ResourceMonitor& statistics, const TimeStep& timeStep);

		static inline std::vector<EntityInfo> _entities;
	};
}
