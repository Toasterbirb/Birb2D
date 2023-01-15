#include "Entities/Animation.hpp"

namespace Birb
{
	namespace Entity
	{
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

		Vector2Int Animation::getAtlasPosition(const int& frame)
		{
			Vector2Int pos;
			int index = frame;

			int texWidth;
			//int texHeight;
			texWidth = sprite.dimensions().x;
			//texHeight = sprite.dimensions().y;

			int spritesPerRow = texWidth / spriteSize.x;
			float fullRowCount = std::floor(index / spritesPerRow);
			float leftOver = ((index / static_cast<float>(spritesPerRow)) - fullRowCount) * spritesPerRow;

			pos.x = leftOver * spriteSize.x;
			pos.y = fullRowCount * spriteSize.y;

			return pos;
		}
	}
}
