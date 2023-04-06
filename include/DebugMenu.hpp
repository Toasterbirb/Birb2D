#pragma once

#include "BaseEntity.hpp"
#include "Color.hpp"
#include "Entities/Text.hpp"
#include "Rect.hpp"
#include "ResourceMonitor.hpp"
#include "Timestep.hpp"
#include <vector>

namespace Birb
{
	// FIXME: Don't store everything into one struct to save on some memory
	struct EntityInfo
	{
		EntityInfo();
		std::string* 	name;
		Rect* 			rect;
		float* 			angle;

		/* Values for text entities */
		Color* 			fg_color;
		Color* 			bg_color;
		std::string* 	text;

		/* Values for progress bar entities */
		float* 			value;
		float* 			max_value;
		float* 			min_value;

		bool deleted;
	};

	class DebugMenu
	{
	public:
		void AddEntity(BaseEntity& entity);
		void AddEntity(Entity::Text& text_entity);

		void EntityMenu();
		static void ResouceMonitor(const Diagnostics::ResourceMonitor& statistics, const TimeStep& timeStep);

	private:
		std::vector<EntityInfo> _entities;
		std::vector<EntityInfo> text_entities;
	};
}
