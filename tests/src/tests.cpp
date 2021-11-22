#ifndef DOCTEST_CONFIG_DISABLE
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 
#endif
//#include "../include/doctest.h"
//#include "../include/RenderWindow.hpp"
//#include "../include/Font.hpp"
//#include "../include/Entity.hpp"
//#include "../include/Utils.hpp"
//#include "../include/Audio.hpp"
//#include "../include/Events.hpp"
//#include "../include/Values.hpp"
//#include "../include/Logger.hpp"
#include "../include/doctest.h"
#include "../../include/RenderWindow.hpp"
#include "../../include/Font.hpp"
#include "../../include/Entity.hpp"
#include "../../include/Utils.hpp"
#include "../../include/Audio.hpp"
#include "../../include/Events.hpp"
#include "../../include/Values.hpp"
#include "../../include/Logger.hpp"


TEST_CASE("logging")
{
	CHECK_NOTHROW(Debug::Log("Log (this is only a test)"));
	CHECK_NOTHROW(Debug::Log("Log (this is only a test)", Debug::log));
	CHECK_NOTHROW(Debug::Log("Warning (this is only a test)", Debug::warning));
	CHECK_NOTHROW(Debug::Log("Error (this is only a test)", Debug::error));
}

// ### Entities ###
TEST_CASE("empty entity")
{
	Birb2D::Entity entity;
	CHECK(entity.getName() == "");
	CHECK(entity.getPos().x == 0);
	CHECK(entity.getPos().y == 0);
	CHECK(entity.getAngle() == 0);
	CHECK(entity.getTex() == NULL);
	CHECK(entity.getCurrentFrame().h == 0);
	CHECK(entity.getCurrentFrame().w == 0);
	CHECK(entity.getCurrentFrame().x == 0);
	CHECK(entity.getCurrentFrame().y == 0);
	CHECK(entity.getText() == "");
}

TEST_CASE("normal texture entity")
{
	Birb2D::Texture texture;
	Birb2D::Entity entity("test entity", Vector2f(0,10), Vector2f(100, 110), texture);

	CHECK(entity.getName() == "test entity");
	CHECK(entity.getPos().x == 0);
	CHECK(entity.getPos().y == 10);
	CHECK(entity.getRect()->h == 110);
	CHECK(entity.getRect()->w == 100);
	CHECK(entity.getRect()->x == 0);
	CHECK(entity.getRect()->y == 10);
	CHECK(entity.getTex() == texture.sdlTexture);
	CHECK(entity.getAngle() == 0);
	CHECK(entity.getCurrentFrame().x == 0);
	CHECK(entity.getCurrentFrame().y == 0);
	CHECK(entity.getCurrentFrame().w == 100);
	CHECK(entity.getCurrentFrame().h == 110);
}

TEST_CASE("texture entity with custom angle")
{
	Birb2D::Texture texture;
	Birb2D::Entity entity("test entity", Vector2f(12, 24), Vector2f(50, 150), 45, texture);
	Birb2D::Entity entity2("test entity", Vector2f(12, 24), Vector2f(50, 150), 390.44, texture);

	CHECK(entity.getName() == "test entity");
	CHECK(entity.getPos().x == 12);
	CHECK(entity.getPos().y == 24);
	CHECK(entity.getRect()->w == 50);
	CHECK(entity.getRect()->h == 150);
	CHECK(entity.getRect()->x == 12);
	CHECK(entity.getRect()->y == 24);
	CHECK(entity.getAngle() == 45);
	CHECK(entity2.getAngle() == 390.44f);
	CHECK(entity.getTex() == texture.sdlTexture);
	CHECK(entity.getCurrentFrame().x == 0);
	CHECK(entity.getCurrentFrame().y == 0);
	CHECK(entity.getCurrentFrame().w == 50);
	CHECK(entity.getCurrentFrame().h == 150);
}

TEST_CASE("scalable texture entity with fractional scale")
{
	Birb2D::Texture texture;
	Birb2D::Entity entity("scalable test entity", Vector2f(24, 64), 2.53, Vector2f(25, 60), texture);

	CHECK(entity.getName() == "scalable test entity");
	CHECK(entity.getPos().x == 24);
	CHECK(entity.getPos().y == 64);
	CHECK(entity.getRect()->x == 24);
	CHECK(entity.getRect()->y == 64);
	CHECK(entity.getAngle() == 0);
	CHECK(entity.getTex() == texture.sdlTexture);
	CHECK(entity.getCurrentFrame().x == 0);
	CHECK(entity.getCurrentFrame().y == 0);
	CHECK(entity.getCurrentFrame().w == 25);
	CHECK(entity.getCurrentFrame().h == 60);
	CHECK(entity.getLocalScale() == 2.53f);
}

TEST_CASE("scalable texture entity with even scale")
{
	Birb2D::Texture texture;
	Birb2D::Entity entity("scalable test entity", Vector2f(24, 64), 3, Vector2f(25, 60), texture);

	CHECK(entity.getName() == "scalable test entity");
	CHECK(entity.getPos().x == 24);
	CHECK(entity.getPos().y == 64);
	CHECK(entity.getRect()->x == 24);
	CHECK(entity.getRect()->y == 64);
	CHECK(entity.getAngle() == 0);
	CHECK(entity.getTex() == texture.sdlTexture);
	CHECK(entity.getCurrentFrame().x == 0);
	CHECK(entity.getCurrentFrame().y == 0);
	CHECK(entity.getCurrentFrame().w == 25);
	CHECK(entity.getCurrentFrame().h == 60);
	CHECK(entity.getLocalScale() == 3);
}

TEST_CASE("scalable texture entity with fractional scale and custom angle")
{
	SDL_Texture* texture;
	Birb2D::Entity entity("scalable test entity", Vector2f(24, 64), 2.53, Vector2f(25, 60), 45, texture);

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
	Birb2D::Entity entity("scalable test entity", Vector2f(24, 64), 4, Vector2f(25, 60), 10.5, texture);

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

Birb2D::Font getTestFont()
{
	Birb2D::RenderWindow window("Test window", 1280, 720, 60);
	SDL_Color color = {0, 0, 0, 0};
	Debug::Log("Getting test font...");
	Birb2D::Font font("../res/fonts/manaspace/manaspc.ttf", color, 32);
	window.cleanUp();

	return font;
}

TEST_CASE("load font")
{
	Birb2D::RenderWindow window("Test window", 1280, 720, 60);
	SDL_Color color = {255, 255, 255, 255};
	CHECK(Birb2D::Font("../res/fonts/manaspace/manaspc.ttf", color, 32).getColor().r == color.r);
	CHECK(Birb2D::Font("../res/fonts/manaspace/manaspc.ttf", color, 32).getColor().g == color.g);
	CHECK(Birb2D::Font("../res/fonts/manaspace/manaspc.ttf", color, 32).getColor().b == color.b);
	window.cleanUp();
}

TEST_CASE("default font")
{
	Birb2D::Font font;

	CHECK(font.getColor().r == Colors::White.r);
	CHECK(font.getColor().g == Colors::White.g);
	CHECK(font.getColor().b == Colors::White.b);
	CHECK(font.getColor().a == Colors::White.a);
}

TEST_CASE("font with custom color")
{
	Birb2D::Font font("../res/fonts/manaspace/manaspc.ttf", Colors::Black, 64);

	CHECK(font.getColor().r == Colors::Black.r);
	CHECK(font.getColor().g == Colors::Black.g);
	CHECK(font.getColor().b == Colors::Black.b);
	CHECK(font.getColor().a == Colors::Black.a);
	CHECK(font.getSize() == 64);
}

TEST_CASE("text entities")
{
	Debug::Log("Getting test font...");
	Birb2D::Font font = getTestFont();
	Birb2D::Entity text_entity("test text", "Testing... :)", Vector2f(15, 45), font);

	CHECK(text_entity.getName() == "test text");
	CHECK(text_entity.getText() == "Testing... :)");
	CHECK(text_entity.getPos().x == 15);
	CHECK(text_entity.getPos().y == 45);
	//CHECK(text_entity.getFont() == font);
}

TEST_CASE("text entity with custom angle and texture")
{
	Debug::Log("Getting test font...");
	Birb2D::Font font = getTestFont();
	SDL_Texture* texture;
	Birb2D::Entity text_entity("test text", "Testing... :)", Vector2f(10, 10), font, texture, 34.44);

	CHECK(text_entity.getName() == "test text");
	CHECK(text_entity.getText() == "Testing... :)");
	CHECK(text_entity.getPos().x == 10);
	CHECK(text_entity.getPos().y == 10);
	//CHECK(text_entity.getFont() == font);
	CHECK(text_entity.getTex() == texture);
	CHECK(text_entity.getAngle() == 34.44f);
}

TEST_CASE("update the text of an existing text texture")
{
	Debug::Log("Getting test font...");
	Birb2D::Font font = getTestFont();
	Birb2D::Entity text_entity("test text", "Testing... :D)", Vector2f(0, 0), font);
	text_entity.updateText("More testing... ;)", text_entity.getTex());

	CHECK_FALSE(text_entity.getText() == "Testing... :D");
	CHECK(text_entity.getText() == "More testing... ;)");
}

TEST_CASE("change the position of an entity")
{
	Birb2D::Texture texture;
	Birb2D::Entity entity("test entity", Vector2f(0, 0), Vector2f(10, 10), texture);
	entity.setPos(Vector2f(505, 406));

	CHECK(entity.getPos().x == 505);
	CHECK(entity.getPos().y == 406);
	CHECK_FALSE(entity.getPos().x == 0);
	CHECK_FALSE(entity.getPos().y == 0);
}

TEST_CASE("change the angle of an entity")
{
	Birb2D::Texture texture;
	Birb2D::Entity entity("test entity", Vector2f(0, 0), Vector2f(10, 10), texture);
	entity.setAngle(34.45f);

	CHECK_FALSE(entity.getAngle() == 0);
	CHECK(entity.getAngle() == 34.45f);
}


// ### Math stuff and other utilities ###
TEST_CASE("Default Vector2f")
{
	Vector2f vector;
	CHECK(vector.x == 0);
	CHECK(vector.y == 0);
}

TEST_CASE("Vector2f with arguments")
{
	CHECK(Vector2f(1, 4).x == 1);
	CHECK(Vector2f(1, 4).y == 4);
	CHECK(Vector2f(1.53f, 5.21f).x == 1.53f);
	CHECK(Vector2f(1.53f, 5.21f).y == 5.21f);
}

TEST_CASE("Default Vector2int")
{
	Vector2int vector;
	CHECK(vector.x == 0);
	CHECK(vector.y == 0);
}

TEST_CASE("Vector2int with arguments")
{
	CHECK(Vector2int(1, 4).x == 1);
	CHECK(Vector2int(1, 4).y == 4);
	CHECK(Vector2int(1.53f, 5.21f).x == 2);
	CHECK(Vector2int(1.53f, 5.21f).y == 5);
}

TEST_CASE("Default Vector3f")
{
	Vector3f vector;
	CHECK(vector.x == 0);
	CHECK(vector.y == 0);
	CHECK(vector.z == 0);
}

TEST_CASE("Vector3f with arguments")
{
	CHECK(Vector3f(1, 4, 2).x == 1);
	CHECK(Vector3f(1, 4, 2).y == 4);
	CHECK(Vector3f(1, 4, 2).z == 2);
	CHECK(Vector3f(1.53f, 5.21f, 2.45f).x == 1.53f);
	CHECK(Vector3f(1.53f, 5.21f, 2.45f).y == 5.21f);
	CHECK(Vector3f(1.53f, 5.21f, 2.45f).z == 2.45f);
}

TEST_CASE("Default Vector3int")
{
	Vector3int vector;
	CHECK(vector.x == 0);
	CHECK(vector.y == 0);
	CHECK(vector.z == 0);
}

TEST_CASE("Vector3int with arguments")
{
	CHECK(Vector3int(1, 4, 2).x == 1);
	CHECK(Vector3int(1, 4, 2).y == 4);
	CHECK(Vector3int(1, 4, 2).z == 2);
	CHECK(Vector3int(1.53f, 5.21f, 2.45f).x == 2);
	CHECK(Vector3int(1.53f, 5.21f, 2.45f).y == 5);
	CHECK(Vector3int(1.53f, 5.21f, 2.45f).z == 2);
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

TEST_CASE("Rect with rounded values (integer)")
{
	Rect customRect(10.54, 20, 30.234, 40.6668);
	Rect roundedRect = customRect.getInt();

	CHECK(roundedRect.x == 11);
	CHECK(roundedRect.y == 20);
	CHECK(roundedRect.w == 30);
	CHECK(roundedRect.h == 41);
}