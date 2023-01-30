#include "BaseEntity.hpp"
#include "Diagnostics.hpp"
#include "Logger.hpp"
#include "Logger.hpp"
#include "Renderwindow.hpp"
#include "ResourceMonitor.hpp"
#include "Resources.hpp"
#include "Values.hpp"

#ifdef DISTCC
#include <iostream>
#endif

namespace Birb
{
	BaseEntity::BaseEntity()
	:name("Default Entity"), angle(0), error_fuse(false)
	{
		++Diagnostics::ResourceMonitor::EntityCount;
	}

	BaseEntity::BaseEntity(const std::string& p_name)
	:name(p_name), angle(0), error_fuse(false)
	{
		++Diagnostics::ResourceMonitor::EntityCount;
	}

	BaseEntity::~BaseEntity()
	{
		--Diagnostics::ResourceMonitor::EntityCount;
	}

    std::ostream &operator<<(std::ostream &stream, const BaseEntity &other)
    {
        stream << "[Name: " << other.name << ", Rect: (" << other.rect << "), Angle: " << other.angle << "]";
        return stream;
    }
}
