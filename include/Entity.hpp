#pragma once

#include "STD.hpp"
#include "Font.hpp"
#include "Utils.hpp"
#include "Timer.hpp"
#include "Color.hpp"
#include "Rect.hpp"
#include "Resources.hpp"
#include "SceneObject.hpp"
#include "Texture.hpp"

namespace Birb
{
	namespace EntityComponent
	{
		/// Text contains details needed to generate a sprite for the Entity in case the Entity is used to display text.
		struct Text
		{
			Text();
			Text(const std::string& text, Font* font, Color* color);
			Text(const std::string& text, Font* font, Color* color, Color* bgColor);

			/* FIXME: figure out how to make these variables private */
			std::string text;
			Font* font;
			Color* color; 	///< Surface color of the text
			Color* bgColor; ///< Background color for the text component

			/* FIXME: Create a constructor for this variable */
			int wrapLength;

			bool operator==(const Text& other) const
			{
				return 	(text 		== other.text
						&& &font 	== &other.font
						&& color 	== other.color
						&& bgColor 	== other.bgColor);
			}
		};

		/// Click adds button functionality to the Entity
		class Click
		{
		public:
			Click();
			Click(const std::function<void()>& p_onClick);
			bool active;
			bool isPressed;
			std::function<void()> onMouseDown;
			std::function<void()> onClick;
            std::function<void()> onHover;
            std::function<void()> onDrag;
		private:
			void AssignPlaceholderEvents();
			static void PlaceHolderMouseDownEvent();
			static void PlaceHolderClickEvent();
			static void PlaceHolderHoverEvent();
			static void PlaceHolderDragEvent();
		};

		/// Animation allows for texture atlas based sprite animations
		struct Animation
		{
			Animation();
			Animation(const Vector2int& p_spriteSize, const int& p_frameCount, const int& p_fps);
			Animation(const Vector2int& p_spriteSize, const int& p_frameCount, const int& p_fps, const bool& p_loop);

			Vector2int spriteSize; ///< The size of one sprite in the atlas. Used for cropping
			int frameCount; ///< Total amount of sprites in the atlas
			int fps;
			bool loop; ///< Start the animation over when it ends
			int frameIndex; ///< Current visible frame
			Timer frameTimer; ///< Timer that is used to play the animation at a set fps

			bool animationQueued; ///< Is the animation queued to start during the next rendering pass
			int lastFrame; ///< Stop playing the animation when this frame is reached


			void StartAnimation(); ///< Start playing the animation from the first frame
			void StartAnimation(const int& startFrame); ///< Start playing the animation from selected frame
			void StartAnimation(const int& startFrame, const int& endFrame); ///< Start playing the animation with custom start and end frame
			void ResetAnimationAtlas(); ///< Reset current frame to 0 and reset the lastFrame to frameCount - 1

			bool operator==(const Animation& other) const
			{
				return 	(fps 			== other.fps
						&& loop 		== other.loop
						&& frameCount 	== other.frameCount
						&& spriteSize 	== other.spriteSize
						&& lastFrame 	== other.lastFrame);
			}
		};

		/// ProgressBar is used to create... well... progress bars
		/// If the entity has a sprite on it. That will be used instead of the fill color
		struct ProgressBar
		{
			ProgressBar();
			ProgressBar(const int& p_borderWidth, Color* p_borderColor, Color* p_backgroundColor, Color* p_fillColor);
			ProgressBar(const int& p_borderWidth, Color* p_borderColor, Color* p_backgroundColor, Color* p_fillColor, const int& p_minValue, const int& p_maxValue, const int& p_value);
			bool active; ///< Setting this value active toggles on the progress bar component

			int borderWidth; ///< Sets the thickness of the borders around the progress bar
			Color* borderColor; ///< Border color around the fill area
			Color* backgroundColor; ///< Background color that is below the filled area
			Color* fillColor; ///< Color that hides the background color

			float minValue; ///< Value where the progress bar should be empty
			float maxValue; ///< Value where the progress bar should be full
			float value; ///< Current progress value

			bool operator==(const ProgressBar& other) const
			{
				return 	(borderWidth 		== other.borderWidth
						&& borderColor 		== other.borderColor
						&& backgroundColor 	== other.backgroundColor
						&& fillColor 		== other.fillColor
						&& minValue 		== other.minValue
						&& maxValue 		== other.maxValue);
			}
		};
	}

	/// Entities are objects that contain all of the information required to render stuff

	/// Entities can be anything really. For example, it could be text or a picture. This could be extended to animations in the future
	class Entity : public SceneObject
	{
	public:
		Entity();
		Entity(const std::string& p_name); ///< Creates an empty Entity object
		Entity(const std::string& p_name, const Rect& rect); ///< Creates an empty Entity object with size and position

		Entity(const std::string& name, const Rect& rect, Texture texture);
		Entity(const std::string& name, const Vector2int& pos, Texture texture);
		Entity(const std::string& name, const Vector2int& pos, Texture texture, const EntityComponent::Animation& animationComponent);

		Entity(const std::string& p_name, const Vector2int& pos, const EntityComponent::Text& p_textComponent); 	///< Creates a Text Entity using a Text

		/* Make it possible to update the Text */
		bool SetText(const std::string& newText); 	///< Change the text in Text and reload the sprite
		void SetFont(const Font& font); 		///< Change the font in Text and reload the sprite
		void SetColor(Color* color); 	///< Change the color in Text and reload the sprite

		std::string name; 		///< Name of the entity. Used for debugging


		float angle; 			///< Sets the rotation of the entity when rendering it
		Rect rect; 				///< Sets the position and the dimensions of the entity
		Vector2f localScale; 	///< Scale modifier for the Entity rendering

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
		Vector2int getAtlasPosition(const int& frame); ///< Get position in a texture atlas given the sprite index

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
		void SetPos(const Vector2f& delta) override;
	};

}
