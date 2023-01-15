#include "Diagnostics.hpp"
#include "BaseEntity.hpp"
#include "Logger.hpp"
#include "Renderwindow.hpp"
#include "Resources.hpp"
#include "Values.hpp"
#include "microprofile.h"

#define PROFILER_GROUP "Entities"
#define PROFILER_COLOR MP_LIGHTGREEN

namespace Birb
{


	void BaseEntity::SetBaseEntityValues()
	{
		angle = 0;
		active = true;
	}

	BaseEntity::BaseEntity()
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Entity construct", PROFILER_COLOR);
		SetBaseEntityValues();
	}

	BaseEntity::BaseEntity(const std::string& p_name)
	:name(p_name)
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Entity construct", PROFILER_COLOR);
		SetBaseEntityValues();
	}

	/* FIXME: Write tests for this constructor */
	BaseEntity::BaseEntity(const std::string& p_name, const Rect& rect, const int& rendering_priority)
	:name(p_name), rect(rect)
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Entity construct", PROFILER_COLOR);
		renderingPriority = rendering_priority;
		SetBaseEntityValues();
	}

	void BaseEntity::RenderFunc()
	{
		Render::DrawEntity(*this);
	}

	void BaseEntity::SetPos(const Vector2& delta)
	{
		rect.x += delta.x;
		rect.y += delta.y;
	}
}
