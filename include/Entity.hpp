#pragma once
#include <iostream>
#include <string.h>
#include <SDL2/SDL_image.h>
#include "RenderWindow.hpp"
#include "Utils.hpp"
#include "Font.hpp"

namespace Birb2D
{
	class RenderWindow;

	class Entity
	{
		public:
			struct Sprite
			{
				Sprite();
				Sprite(std::string p_filePath); // Initialize struct with a texture
				Texture texture;
				std::string filePath;
			};

			struct Text
			{
				Text();
				Text(std::string p_text, Birb2D::Font p_font, RenderWindow p_window);
				std::string value;
				Birb2D::Font font;
				Rect frame; 			/* 	Frame for the text element inside of the entity.
											The text frame could be smaller than the actual entity	*/

				Texture texture; 		/* 	Texture to store the text texture into */
			};


			Entity();
			Entity(std::string p_name, Vector2f p_position);
			Entity(std::string p_name, Rect p_rect);
			Entity(std::string p_name, Rect p_rect, float p_angle);
			Entity(std::string p_name, Rect p_rect, float p_angle, Vector2f p_objectCenter);
			Entity(std::string p_name, Rect p_rect, float p_angle, Vector2f p_objectCenter, Vector2f p_anchor);

			std::string name = "Default entity"; 	/* Used to identify the entity */
			Rect rect = Rect(0,0,0,0); 	/* Position and local scale */
			float angle = 0; 			/* Rotation of the entity in 2D space */

			float localScale = 1;		/* 	Multiplier for the size of the entity. Useful when the original
								   			size needs to be kept intact */

			int z = 0; 					/* 	Priority / depth. 0 is the default and the lowest priority.
										   	Higher priority means, that the entity will be rendered on top
								   			on other entities */

			/* Anchoring */
			Vector2f objectCenter = Vector2f(0, 0); /* 	Center point of the entity. Entity position uses
														this point as the top left corner. Values range
														from 0f-1f 0,0 being the top left corner and 1,1
														being the bottom right corner	*/
			
			Vector2f anchor = Vector2f(0, 0); 		/* 	Point on screen that the objectCenter is positioned
														relatively to. For example, anchor 1,1 would be the
														bottom right corner. If the center point would be 1,1
														in that case, the entity would be positioned to the
														bottom right corner and follow the corner when the
														window is resized.	*/

			/* Extra stuff to make the entity show up on the screen */
			Sprite sprite; 				/* 	Sprites allow entities to render stuff, like pictures,
											animations etc. */

			Text text; 					/*  Text allows for creating text textures dynamically. 
											The text in the texture can be changed runtime */

	};


}
