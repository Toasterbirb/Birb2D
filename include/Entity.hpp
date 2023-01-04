#pragma once

#include "STD.hpp"
#include "EntityComponent.hpp"
#include "Rect.hpp"
#include "SceneObject.hpp"
#include "Texture.hpp"

namespace Birb
{

	/// Entities are objects that contain all of the information required to render stuff

	/// Entities can be anything really. For example, it could be text or a picture. This could be extended to animations in the future
	class Entity : public SceneObject
	{
	public:
		Entity();
		Entity(const std::string& p_name); ///< Creates an empty Entity object
		Entity(const std::string& p_name, const Rect& rect, const int& rendering_priority = 0); ///< Creates an empty Entity object with size and position

		Entity(const std::string& name, const Rect& rect, Texture texture, const int& rendering_priority = 0);
		Entity(const std::string& name, const Vector2Int& pos, Texture texture, const int& rendering_priority = 0);
		Entity(const std::string& name, const Vector2Int& pos, Texture texture, const EntityComponent::Animation& animationComponent, const int& rendering_priority = 0);

		Entity(const std::string& p_name, const Vector2Int& pos, const EntityComponent::Text& p_textComponent, const int& rendering_priority = 0); 	///< Creates a Text Entity using a Text

		/* Make it possible to update the Text */
		bool SetText(const std::string& newText); 	///< Change the text in Text and reload the sprite
		void SetFont(const Font& font); 		///< Change the font in Text and reload the sprite
		void SetTextColor(Color* color); 	///< Change the color in Text and reload the sprite

		std::string name; 		///< Name of the entity. Used for debugging


		float angle; 			///< Sets the rotation of the entity when rendering it
		Rect rect; 				///< Sets the position and the dimensions of the entity
		Vector2 localScale; 	///< Scale modifier for the Entity rendering

		/* Sprite handlings */
		Texture sprite; 		///< Sprite to be rendered

		EntityComponent::Text textComponent; 				///< Enables the rendering of Text
		EntityComponent::Click clickComponent; 				///< Enables button-like functionality
		EntityComponent::Animation animationComponent; 		///< Enables animations for sprite rendering
		EntityComponent::ProgressBar progressBarComponent; 	///< Turns the entity into a progress bar
		bool LoadSprite(); 				///< Create a sprite for the Entity using details found in the textComponent variable
		bool ReloadSprite(); 			///< Destroy the old sprite and create a new one. Useful for refreshing text after editing the textComponent variable
		void SetBaseEntityValues(); 	///< Used to set some default value when they aren't provided during Entity initialization
		void CenterRelativeTo(const Rect& rect);

		/* Informational functions */
		bool isHovering(); ///< Check if the cursor is hovering over this entity
		Vector2Int getAtlasPosition(const int& frame); ///< Get position in a texture atlas given the sprite index

		bool operator==(const Entity& other) const
		{
			return 	(&sprite 					== &other.sprite
					&& localScale 				== other.localScale
					&& textComponent 			== other.textComponent
					&& &clickComponent 			== &other.clickComponent
					&& &animationComponent 		== &other.animationComponent
					&& &progressBarComponent 	== &other.progressBarComponent);
		}

	private:
		void RenderFunc() override;
		void SetPos(const Vector2& delta) override;
	};

}
