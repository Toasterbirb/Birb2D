#pragma once

#include "BaseEntity.hpp"
#include "Color.hpp"
#include "Entities/Text.hpp"
#include "Rect.hpp"
#include "ResourceMonitor.hpp"
#include "Timestep.hpp"
#include "imgui.h"
#include <vector>

namespace Birb
{
	struct EntityInfo
	{
		EntityInfo();
		std::string* 	name;
		Rect* 			rect;
		float* 			angle;
		float 			rect_color[4];

		bool deleted;
	};

	class DebugMenu
	{
	public:
		void AddEntity(BaseEntity& entity);
		void Clear(); /// Clears the entity list

		void EntityMenu();
		static void ResouceMonitor(const Diagnostics::ResourceMonitor& statistics, const TimeStep& timeStep);

	private:
		std::vector<EntityInfo> _entities;
	};
}
