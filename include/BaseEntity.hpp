#pragma once

#ifndef DISTCC
#include "STD.hpp"
#else
#include <string>
#include <iosfwd>
#endif


#include "ErrorFuse.hpp"
#include "EntityComponent.hpp"
#include "Rect.hpp"
#include "SceneObject.hpp"

namespace Birb
{

	/// Entities are objects that contain all of the information required to render stuff

	/// Entities can be anything really. For example, it could be text or a picture. This could be extended to animations in the future
	class BaseEntity : public ErrorFuse
	{
	public:
		BaseEntity();
		~BaseEntity();
		BaseEntity(const std::string& p_name); ///< Creates an empty Entity object
		BaseEntity(const std::string& p_name, const Rect& rect, const int& rendering_priority = 0); ///< Creates an empty Entity object with size and position
		void Debug(std::string name); ///< Add this entity into the debug menu entity list

		std::string name; 		///< Name of the entity. Used for debugging

		float angle; 			///< Sets the rotation of the entity when rendering it
		Rect rect; 				///< Sets the position and the dimensions of the entity

		bool operator==(const BaseEntity& other) const
		{
			return 	(name 		== other.name
					&& angle 	== other.angle
					&& rect 	== other.rect);
		}

	private:
		bool error_fuse;
		int debug_menu_index;
	};

	std::ostream &operator<<(std::ostream &stream, const BaseEntity &other);
}
