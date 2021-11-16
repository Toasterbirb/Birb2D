#ifndef DOCTEST_CONFIG_DISABLE
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 
#endif
#include "../include/doctest.h"
#include "../include/RenderWindow.hpp"
#include "../include/Font.hpp"
#include "../include/Entity.hpp"
#include "../include/Utils.hpp"
#include "../include/Audio.hpp"
#include "../include/Events.hpp"

// ### Entities ###
TEST_CASE("normal texture entity")
{
	SDL_Texture* texture;
	Entity entity("test entity", Vector2f(0,10), Vector2f(100, 110), texture);

	CHECK(entity.getName() == "test entity");
	CHECK(entity.getPos().x == 0);
	CHECK(entity.getPos().y == 10);
	CHECK(entity.getRect()->h == 110);
	CHECK(entity.getRect()->w == 100);
	CHECK(entity.getRect()->x == 0);
	CHECK(entity.getRect()->y == 10);
	CHECK(entity.getTex() == texture);
	CHECK(entity.getAngle() == 0);
	CHECK(entity.getCurrentFrame().x == 0);
	CHECK(entity.getCurrentFrame().y == 0);
	CHECK(entity.getCurrentFrame().w == 100);
	CHECK(entity.getCurrentFrame().h == 110);
}

TEST_CASE("texture entity with custom angle")
{
	SDL_Texture* texture;
	Entity entity("test entity", Vector2f(12, 24), Vector2f(50, 150), 45, texture);
	Entity entity2("test entity", Vector2f(12, 24), Vector2f(50, 150), 390.44, texture);

	CHECK(entity.getName() == "test entity");
	CHECK(entity.getPos().x == 12);
	CHECK(entity.getPos().y == 24);
	CHECK(entity.getRect()->w == 50);
	CHECK(entity.getRect()->h == 150);
	CHECK(entity.getRect()->x == 12);
	CHECK(entity.getRect()->y == 24);
	CHECK(entity.getAngle() == 45);
	CHECK(entity2.getAngle() == 390.44f);
	CHECK(entity.getTex() == texture);
	CHECK(entity.getCurrentFrame().x == 0);
	CHECK(entity.getCurrentFrame().y == 0);
	CHECK(entity.getCurrentFrame().w == 50);
	CHECK(entity.getCurrentFrame().h == 150);
}

TEST_CASE("scalable texture entity with fractional scale")
{
	SDL_Texture* texture;
	Entity entity("scalable test entity", Vector2f(24, 64), 2.53, Vector2f(25, 60), texture);

	CHECK(entity.getName() == "scalable test entity");
	CHECK(entity.getPos().x == 24);
	CHECK(entity.getPos().y == 64);
	CHECK(entity.getRect()->x == 24);
	CHECK(entity.getRect()->y == 64);
	CHECK(entity.getAngle() == 0);
	CHECK(entity.getTex() == texture);
	CHECK(entity.getCurrentFrame().x == 0);
	CHECK(entity.getCurrentFrame().y == 0);
	CHECK(entity.getCurrentFrame().w == 63.25f);
	CHECK(entity.getCurrentFrame().h == 151.8f);
}

TEST_CASE("scalable texture entity with even scale")
{
	SDL_Texture* texture;
	Entity entity("scalable test entity", Vector2f(24, 64), 3, Vector2f(25, 60), texture);

	CHECK(entity.getName() == "scalable test entity");
	CHECK(entity.getPos().x == 24);
	CHECK(entity.getPos().y == 64);
	CHECK(entity.getRect()->x == 24);
	CHECK(entity.getRect()->y == 64);
	CHECK(entity.getAngle() == 0);
	CHECK(entity.getTex() == texture);
	CHECK(entity.getCurrentFrame().x == 0);
	CHECK(entity.getCurrentFrame().y == 0);
	CHECK(entity.getCurrentFrame().w == 75);
	CHECK(entity.getCurrentFrame().h == 180);
}

TEST_CASE("scalable texture entity with fractional scale and custom angle")
{
	SDL_Texture* texture;
	Entity entity("scalable test entity", Vector2f(24, 64), 2.53, Vector2f(25, 60), 45, texture);

	CHECK(entity.getName() == "scalable test entity");
	CHECK(entity.getPos().x == 24);
	CHECK(entity.getPos().y == 64);
	CHECK(entity.getCurrentFrame().w == 63.25);
	CHECK(entity.getCurrentFrame().h == 151.8f);
	CHECK(entity.getRect()->x == 24);
	CHECK(entity.getRect()->y == 64);
	CHECK(entity.getAngle() == 45);
	CHECK(entity.getTex() == texture);
}

TEST_CASE("scalable texture entity with even scale and custom angle")
{
	SDL_Texture* texture;
	Entity entity("scalable test entity", Vector2f(24, 64), 4, Vector2f(25, 60), 10.5, texture);

	CHECK(entity.getName() == "scalable test entity");
	CHECK(entity.getPos().x == 24);
	CHECK(entity.getPos().y == 64);
	CHECK(entity.getCurrentFrame().w == 100);
	CHECK(entity.getCurrentFrame().h == 240);
	CHECK(entity.getRect()->x == 24);
	CHECK(entity.getRect()->y == 64);
	CHECK(entity.getAngle() == 10.5);
	CHECK(entity.getTex() == texture);
}

Font getTestFont()
{
	RenderWindow window("Test window", 1280, 720, 60);
	TTF_Font* manascpace = window.loadFont("../res/fonts/manaspace/manaspc.ttf", 32);
	SDL_Color color = {0, 0, 0};
	Font font(manascpace, color, 32);

	return font;
}

TEST_CASE("text entities")
{
	Font font = getTestFont();
	Entity text_entity("test text", "Testing... :)", Vector2f(15, 45), &font);

	CHECK(text_entity.getName() == "test text");
	CHECK(text_entity.getText() == "Testing... :)");
	CHECK(text_entity.getPos().x == 15);
	CHECK(text_entity.getPos().y == 45);
	CHECK(text_entity.getFont() == &font);
}

TEST_CASE("text entity with custom angle and texture")
{
	Font font = getTestFont();
	SDL_Texture* texture;
	Entity text_entity("test text", "Testing... :)", Vector2f(10, 10), &font, texture, 34.44);

	CHECK(text_entity.getName() == "test text");
	CHECK(text_entity.getText() == "Testing... :)");
	CHECK(text_entity.getPos().x == 10);
	CHECK(text_entity.getPos().y == 10);
	CHECK(text_entity.getFont() == &font);
	CHECK(text_entity.getTex() == texture);
	CHECK(text_entity.getAngle() == 34.44f);
}

TEST_CASE("update the text of an existing text texture")
{
	Font font = getTestFont();
	Entity text_entity("test text", "Testing... :D)", Vector2f(0, 0), &font);
	text_entity.updateText("More testing... ;)", text_entity.getTex());

	CHECK_FALSE(text_entity.getText() == "Testing... :D");
	CHECK(text_entity.getText() == "More testing... ;)");
}

TEST_CASE("change the position of an entity")
{
	SDL_Texture* texture;
	Entity entity("test entity", Vector2f(0, 0), Vector2f(10, 10), texture);
	entity.setPos(Vector2f(505, 406));

	CHECK(entity.getPos().x == 505);
	CHECK(entity.getPos().y == 406);
	CHECK_FALSE(entity.getPos().x == 0);
	CHECK_FALSE(entity.getPos().y == 0);
}

TEST_CASE("change the angle of an entity")
{
	SDL_Texture* texture;
	Entity entity("test entity", Vector2f(0, 0), Vector2f(10, 10), texture);
	entity.setAngle(34.45f);

	CHECK_FALSE(entity.getAngle() == 0);
	CHECK(entity.getAngle() == 34.45f);
}


// ### Math stuff and other utilities ###
TEST_CASE("Default Vector2f")
{
	CHECK(Vector2f().x == 0);
	CHECK(Vector2f().y == 0);
}

TEST_CASE("Vector2f with arguments")
{
	CHECK(Vector2f(1, 4).x == 1);
	CHECK(Vector2f(1, 4).y == 4);
	CHECK(Vector2f(1.53, 5.21).x == 1.53f);
	CHECK(Vector2f(1.53, 5.21).y == 5.21f);
}

TEST_CASE("Default Rect")
{
	Rect defaultRect;
	CHECK(defaultRect.x == 0);
	CHECK(defaultRect.y == 0);
	CHECK(defaultRect.w == 0);
	CHECK(defaultRect.h == 0);

}

TEST_CASE("Rect with arguments")
{
	Rect customRect(10.54, 20, 30.234, 40.6668);
	CHECK(customRect.x == 10.54f);
	CHECK(customRect.y == 20);
	CHECK(customRect.w == 30.234f);
	CHECK(customRect.h == 40.6668f);
}
