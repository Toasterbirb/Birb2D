#include "BaseEntity.hpp"
#include "DebugMenu.hpp"

#ifdef DISTCC
#include <iostream>
#endif

namespace Birb
{
	BaseEntity::BaseEntity()
	:name("Default Entity"), angle(0), error_fuse(false), debug_menu_index(-1)
	{
		++Diagnostics::ResourceMonitor::EntityCount;
	}

	BaseEntity::BaseEntity(const std::string& p_name)
	:name(p_name), angle(0), error_fuse(false)
	{
		debug_menu_index = DebugMenu::AddEntity(*this);
		++Diagnostics::ResourceMonitor::EntityCount;
	}

	BaseEntity::~BaseEntity()
	{
		if (debug_menu_index != -1)
			DebugMenu::_entities[debug_menu_index].deleted = true;

		--Diagnostics::ResourceMonitor::EntityCount;
	}

	void BaseEntity::Debug(std::string name)
	{
		this->name = name;
		debug_menu_index = DebugMenu::AddEntity(*this);
	}

    std::ostream &operator<<(std::ostream &stream, const BaseEntity &other)
    {
        stream << "[Name: " << other.name << ", Rect: (" << other.rect << "), Angle: " << other.angle << "]";
        return stream;
    }
}
