#include "Entities/Animation.hpp"
#include "Render.hpp"
#include "Values.hpp"

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

		Animation::Animation(const Texture& sprite, const Vector2Int& sprite_size, int frame_count, int fps)
		:spriteSize(sprite_size), frameCount(frame_count), fps(fps), lastFrame(frame_count - 1), sprite(sprite)
		{
			frameIndex 		= 0;
			loop 			= false;
			animationQueued = false;
			rect.w 			= sprite.dimensions().x;
			rect.h 			= sprite.dimensions().y;
		}

		Animation::Animation(const Texture& sprite, const Vector2Int& sprite_size, int frame_count, int fps, bool loop)
		:spriteSize(sprite_size), frameCount(frame_count), fps(fps), loop(loop), lastFrame(frame_count - 1), sprite(sprite)
		{
			frameIndex 		= 0;
			animationQueued = false;
			rect.w 			= sprite.dimensions().x;
			rect.h 			= sprite.dimensions().y;
		}

		void Animation::Construct(const Texture& sprite, const Vector2Int& sprite_size, int frame_count, int fps, bool loop)
		{
			this->sprite = sprite;
			this->spriteSize = sprite_size;
			this->frameCount = frame_count;
			this->fps = fps;
			this->loop = loop;

			frameIndex 		= 0;
			animationQueued = false;
			rect.w 			= sprite.dimensions().x;
			rect.h 			= sprite.dimensions().y;
		}

		void Animation::ResetAnimationAtlas()
		{
			frameIndex = 0;
			lastFrame = frameCount - 1;
		}

		void Animation::StartAnimation()
		{
			assert(sprite.isLoaded());
			ResetAnimationAtlas();
			animationQueued = true;
		}

		void Animation::StartAnimation(int p_startFrame)
		{
			assert(sprite.isLoaded());
			frameIndex = p_startFrame;
			lastFrame = frameCount - 1;
			animationQueued = true;
		}

		void Animation::StartAnimation(int p_startFrame, int p_lastFrame)
		{
			assert(sprite.isLoaded());
			assert(p_startFrame < p_lastFrame);
			frameIndex = p_startFrame;
			lastFrame = p_lastFrame;
			animationQueued = true;
		}

		Vector2Int Animation::getAtlasPosition(int frame)
		{
			assert(frame >= 0);

			Vector2Int pos;
			int index = frame;

			int texWidth;
			//int texHeight;
			texWidth = sprite.dimensions().x;
			//texHeight = sprite.dimensions().y;

			int spritesPerRow = texWidth / spriteSize.x;
			int fullRowCount = std::floor(index / spritesPerRow);
			int leftOver = ((index / static_cast<float>(spritesPerRow)) - fullRowCount) * spritesPerRow;

			pos.x = leftOver * spriteSize.x;
			pos.y = fullRowCount * spriteSize.y;

			return pos;
		}

		void Animation::StepFrame()
		{
			/* Set the current atlas position to the next frame */
			if (animationQueued || loop)
			{
				Vector2Int atlasPos = getAtlasPosition(frameIndex);
				src.x = atlasPos.x;
				src.y = atlasPos.y;
				src.w = spriteSize.x;
				src.h = spriteSize.y;

				dst.x = rect.x - (Global::RenderVars::CameraPosition.x * world_space);
				dst.y = rect.y - (Global::RenderVars::CameraPosition.y * world_space);
				dst.w = rect.w; // * entity->localScale.x;
				dst.h = rect.h; // * entity->localScale.y;

				assert(fps != 0 && "Zero division");
				if (frameTimer.running && frameTimer.ElapsedSeconds() >= (1.0 / fps))
				{
					if (frameIndex < lastFrame)
					{
						frameIndex++;
						frameTimer.Start();
					}
				}
				else if (!frameTimer.running)
				{
					/* Start the frame timer */
					frameTimer.Start();
				}

				if (loop && frameIndex >= lastFrame)
				{
					frameIndex = 0;
				}
				else if (animationQueued && frameIndex >= lastFrame)
				{
					frameIndex = lastFrame;
					animationQueued = false;
				}
			}
		}

		void Animation::RenderFunc()
		{
			StepFrame();
			if (!Render::DrawTexture(sprite, src, dst, angle))
				BlowErrorFuse();
		}

		void Animation::SetPos(const Vector2& delta)
		{
			rect.x += delta.x;
			rect.y += delta.y;
		}
	}
}
