#pragma once

#include <functional>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Utils.hpp"
#include "Timer.hpp"

namespace Birb
{
	namespace EntityComponent
	{
		/// TextComponent contains details needed to generate a sprite for the Entity in case the Entity is used to display text.
		struct TextComponent
		{
			TextComponent();
			TextComponent(std::string p_text, TTF_Font* font, SDL_Color* p_color);
			TextComponent(std::string p_text, TTF_Font* font, SDL_Color* p_color, SDL_Color* p_bgColor);
			std::string text;
			TTF_Font* font;
			SDL_Color* color; 	///< Surface color of the text
			SDL_Color* bgColor; ///< Background color for the text component
		};

		/// ClickComponent adds button functionality to the Entity
		struct ClickComponent
		{
			ClickComponent();
			ClickComponent(std::function<void()> p_onClick);
			bool active;
			std::function<void()> onClick;
		};

		/// AnimationComponent allows for texture atlas based sprite animations
		struct AnimationComponent
		{
			AnimationComponent();
			AnimationComponent(Vector2int p_spriteSize, int p_frameCount, int p_fps);
			AnimationComponent(Vector2int p_spriteSize, int p_frameCount, int p_fps, bool p_loop);

			int fps;
			bool loop; ///< Start the animation over when it ends
			int frameIndex; ///< Current visible frame
			int frameCount; ///< Total amount of sprites in the atlas
			Vector2int spriteSize; ///< The size of one sprite in the atlas. Used for cropping
			Timer frameTimer;

			bool animationQueued;
			int lastFrame;


			void StartAnimation();
			void StartAnimation(int startFrame);
			void StartAnimation(int startFrame, int endFrame);
			void ResetAnimationAtlas();
		};
	}

	/// Entities are objects that contain all of the information required to render stuff
	
	/// Entities can be anything really. For example, it could be text or a picture. This could be extended to animations in the future
	struct Entity
	{
		Entity(); ///< Creates empty Entity object
		Entity(std::string p_name, Rect p_rect, SDL_Texture* p_texture); 			///< Creates an Entity with a SDL_Texture to render with custom scale
		Entity(std::string p_name, Vector2int pos, EntityComponent::TextComponent p_textComponent); 	///< Creates a Text Entity using a TextComponent
		Entity(std::string p_name, Vector2int pos, SDL_Texture* p_texture); 		///< Creates an Entity with a SDL_Texture to render without specifying a scale

		/* Make it possible to update the TextComponent */
		void SetText(std::string newText); 	///< Change the text in TextComponent and reload the sprite
		void SetFont(TTF_Font* font); 		///< Change the font in TextComponent and reload the sprite
		void SetColor(SDL_Color* color); 	///< Change the color in TextComponent and reload the sprite

		std::string name; 		///< Name of the entity. Used for debugging

		/* Sprite handlings */
		SDL_Texture* sprite; 	///< Sprite to be rendered

		float angle; 			///< Sets the rotation of the entity when rendering it
		Rect rect; 				///< Sets the position and the dimensions of the entity
		Vector2f localScale; 	///< Scale modifier for the Entity rendering

		EntityComponent::TextComponent textComponent; 			///< Enables the rendering of Text
		EntityComponent::ClickComponent clickComponent; 		///< Enables button-like functionality
		EntityComponent::AnimationComponent animationComponent; ///< Enables animations for sprite rendering
		void LoadSprite(); 				///< Create a sprite for the Entity using details found in the textComponent variable
		void ReloadSprite(); 			///< Destroy the old sprite and create a new one. Useful for refreshing text after editing the textComponent variable
		void SetBaseEntityValues(); 	///< Used to set some default value when they aren't provided during Entity initialization

		/* Informational functions */
		bool isHovering(); ///< Check if the cursor is hovering over this entity
		Vector2int getAtlasPosition(int frame); ///< Get position in a texture atlas given the sprite index
	};

}
