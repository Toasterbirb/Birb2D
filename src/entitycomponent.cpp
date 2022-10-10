#include "Diagnostics.hpp"
#include "EntityComponent.hpp"

namespace Birb
{
	namespace EntityComponent
	{
		Text::Text()
		{
			text 	= "";
			font 	= NULL;
			color 	= NULL;
			bgColor = NULL;
			wrapLength = 0;
		}

		Text::Text(const std::string& text, Font* font, Color* color)
		:text(text), font(font), color(color)
		{
			bgColor = NULL;
			wrapLength = 0;
		}

		Text::Text(const std::string& text, Font* font, Color* color, Color* bgColor)
		:text(text), font(font), color(color), bgColor(bgColor)
		{
			wrapLength = 0;
		}

		void Click::PlaceHolderMouseDownEvent()
		{
#ifdef DEBUG
			if (Diagnostics::Debugging::Buttons)
				Debug::Log("Placeholder onMouseDown event");
#endif
			return;
		}

		void Click::PlaceHolderClickEvent()
		{
#ifdef DEBUG
            if (Diagnostics::Debugging::Buttons)
                Debug::Log("Placeholder onClick event");
#endif
			return;
		}

        void Click::PlaceHolderHoverEvent()
        {
#ifdef DEBUG
            if (Diagnostics::Debugging::Buttons)
                Debug::Log("Placeholder onHover event");
#endif
			return;
        }

        void Click::PlaceHolderDragEvent()
        {
#ifdef DEBUG
            if (Diagnostics::Debugging::Buttons)
                Debug::Log("Placeholder onDrag event");
#endif
			return;
        }

		void Click::AssignPlaceholderEvents()
		{
			onMouseDown = PlaceHolderMouseDownEvent;
            onHover = PlaceHolderHoverEvent;
            onDrag  = PlaceHolderDragEvent;
		}

		Click::Click()
		{
			AssignPlaceholderEvents();
			onClick 	= PlaceHolderClickEvent;
			active 		= true;
			isPressed 	= false;
		}

		Click::Click(const std::function<void()>& p_onClick)
		:onClick(p_onClick)
		{
			AssignPlaceholderEvents();
			active 		= true;
			isPressed 	= false;
		}

		Animation::Animation()
		{
			fps 			= 24;
			loop 			= false;
			frameIndex 		= 0;
			frameCount 		= 0;
			spriteSize 		= { 16, 16 };
			animationQueued = false;
		}

		Animation::Animation(const Vector2Int& p_spriteSize, const int& p_frameCount, const int& p_fps)
		:spriteSize(p_spriteSize), frameCount(p_frameCount), fps(p_fps), lastFrame(p_frameCount - 1)
		{
			frameIndex 		= 0;
			loop 			= false;
			animationQueued = false;
		}

		Animation::Animation(const Vector2Int& p_spriteSize, const int& p_frameCount, const int& p_fps, const bool& p_loop)
		:spriteSize(p_spriteSize), frameCount(p_frameCount), fps(p_fps), loop(p_loop), lastFrame(p_frameCount - 1)
		{
			frameIndex 		= 0;
			animationQueued = false;
		}


		void Animation::ResetAnimationAtlas()
		{
			frameIndex = 0;
			lastFrame = frameCount - 1;
		}

		void Animation::StartAnimation()
		{
			ResetAnimationAtlas();
			animationQueued = true;
		}

		void Animation::StartAnimation(const int& p_startFrame)
		{
			frameIndex = p_startFrame;
			lastFrame = frameCount - 1;
			animationQueued = true;
		}

		void Animation::StartAnimation(const int& p_startFrame, const int& p_lastFrame)
		{
			frameIndex = p_startFrame;
			lastFrame = p_lastFrame;
			animationQueued = true;
		}

		ProgressBar::ProgressBar()
		{
			borderWidth 	= 1;
			borderColor 	= &Birb::Colors::White;
			backgroundColor = &Birb::Colors::Black;
			fillColor 		= &Birb::Colors::White;

			minValue = 0;
			maxValue = 1;
			value = 0;

			active = false;
		}

		ProgressBar::ProgressBar(const int& p_borderWidth, Color* p_borderColor, Color* p_backgroundColor, Color* p_fillColor)
		:borderWidth(p_borderWidth), borderColor(p_borderColor), backgroundColor(p_backgroundColor), fillColor(p_fillColor)
		{
			minValue = 0;
			maxValue = 1;
			value = 0.25f;

			active = true;
		}

		ProgressBar::ProgressBar(const int& p_borderWidth, Color* p_borderColor, Color* p_backgroundColor, Color* p_fillColor, const int& p_minValue, const int& p_maxValue, const int& p_value)
		:borderWidth(p_borderWidth), borderColor(p_borderColor), backgroundColor(p_backgroundColor), fillColor(p_fillColor), minValue(p_minValue), maxValue(p_maxValue), value(p_value)
		{
			active = true;
		}
	}
}
