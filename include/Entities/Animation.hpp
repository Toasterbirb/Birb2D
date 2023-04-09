#pragma once

#include "Timer.hpp"
#include "Texture.hpp"
#include "Vector/Vector2Int.hpp"
#include "BaseEntity.hpp"

namespace Birb
{
	namespace Entity
	{
		/// Animation allows for texture atlas based sprite animations
		class Animation : public BaseEntity, public SceneObject
		{
		public:
			Animation();
			Animation(const Texture& sprite, const Vector2Int& sprite_size, int frame_count, int fps);
			Animation(const Texture& sprite, const Vector2Int& sprite_size, int frame_count, int fps, bool loop);

			void Construct(const Texture& sprite, const Vector2Int& sprite_size, int frame_count, int fps, bool loop = false);

			Vector2Int spriteSize; ///< The size of one sprite in the atlas. Used for cropping
			int frameCount; ///< Total amount of sprites in the atlas
			int fps;
			bool loop; ///< Start the animation over when it ends
			int frameIndex; ///< Current visible frame
			Timer frameTimer; ///< Timer that is used to play the animation at a set fps

			bool animationQueued; ///< Is the animation queued to start during the next rendering pass
			int lastFrame; ///< Stop playing the animation when this frame is reached

			Texture sprite;

			void StartAnimation(); ///< Start playing the animation from the first frame
			void StartAnimation(int startFrame); ///< Start playing the animation from selected frame
			void StartAnimation(int startFrame, int endFrame); ///< Start playing the animation with custom start and end frame
			void ResetAnimationAtlas(); ///< Reset current frame to 0 and reset the lastFrame to frameCount - 1
			Vector2Int getAtlasPosition(int frame);

			bool operator==(const Animation& other) const
			{
				return 	(fps 			== other.fps
						&& loop 		== other.loop
						&& frameCount 	== other.frameCount
						&& spriteSize 	== other.spriteSize
						&& lastFrame 	== other.lastFrame);
			}

		private:
			void StepFrame();
			SDL_Rect src;
			SDL_Rect dst;

			void RenderFunc() override;
			void SetPos(const Vector2& delta) override;
		};
	}
}
