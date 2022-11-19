#pragma once

#include "Timer.hpp"
#include "Vector/Vector2Int.hpp"

namespace Birb
{
	namespace EntityComponent
	{
		/// Animation allows for texture atlas based sprite animations
		struct Animation
		{
			Animation();
			Animation(const Vector2Int& p_spriteSize, const int& p_frameCount, const int& p_fps);
			Animation(const Vector2Int& p_spriteSize, const int& p_frameCount, const int& p_fps, const bool& p_loop);

			Vector2Int spriteSize; ///< The size of one sprite in the atlas. Used for cropping
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
	}
}
