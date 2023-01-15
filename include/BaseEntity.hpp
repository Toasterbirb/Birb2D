#pragma once

#ifndef DISTCC
#include "STD.hpp"
#else
#include <string>
#endif


#include "EntityComponent.hpp"
#include "Rect.hpp"
#include "SceneObject.hpp"

namespace Birb
{

	/// Entities are objects that contain all of the information required to render stuff

	/// Entities can be anything really. For example, it could be text or a picture. This could be extended to animations in the future
	class BaseEntity : public SceneObject
	{
	public:
		BaseEntity();
		BaseEntity(const std::string& p_name); ///< Creates an empty Entity object
		BaseEntity(const std::string& p_name, const Rect& rect, const int& rendering_priority = 0); ///< Creates an empty Entity object with size and position

		std::string name; 		///< Name of the entity. Used for debugging

		float angle; 			///< Sets the rotation of the entity when rendering it
		Rect rect; 				///< Sets the position and the dimensions of the entity

		void SetBaseEntityValues(); 	///< Used to set some default value when they aren't provided during Entity initialization

	private:
		void RenderFunc() override;
		void SetPos(const Vector2& delta) override;
	};

}
