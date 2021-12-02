#ifndef DOCTEST_CONFIG_DISABLE
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 
#endif

#include "../include/doctest.h"
#include "../../include/RenderWindow.hpp"
#include "../../include/Font.hpp"
#include "../../include/Entity.hpp"
#include "../../include/Utils.hpp"
#include "../../include/Audio.hpp"
#include "../../include/Events.hpp"
#include "../../include/Values.hpp"
#include "../../include/Logger.hpp"
#include "../../include/Widgets.hpp"


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
	CHECK(entity.name == "Default entity");
	CHECK(entity.rect.x == 0);
	CHECK(entity.rect.y == 0);
	CHECK(entity.rect.w == 0);
	CHECK(entity.rect.h == 0);
	CHECK(entity.angle == 0);
}

TEST_CASE("entity with a texture")
{
	Birb2D::Texture texture;
	Birb2D::Entity entity("test entity", Rect(0, 10, 100, 110));
	entity.sprite.texture = texture;

	CHECK(entity.name == "test entity");
	CHECK(entity.rect.x == 0);
	CHECK(entity.rect.y == 10);
	CHECK(entity.rect.h == 110);
	CHECK(entity.rect.w == 100);
	CHECK(entity.sprite.texture.sdlTexture == texture.sdlTexture);
	CHECK(entity.angle == 0);
}

TEST_CASE("entity with texture and custom angle")
{
	Birb2D::Texture texture;
	Birb2D::Entity entity("test entity", Rect(12, 24, 50, 150), 45);
	entity.sprite.texture = texture;

	CHECK(entity.name == "test entity");
	CHECK(entity.rect.x == 12);
	CHECK(entity.rect.y == 24);
	CHECK(entity.rect.w == 50);
	CHECK(entity.rect.h == 150);
	CHECK(entity.angle == 45);
	CHECK(entity.sprite.texture.sdlTexture == texture.sdlTexture);
}

TEST_CASE("entity with a texture and custom local scale")
{
	Birb2D::Texture texture;
	Birb2D::Entity entity("scalable test entity", Rect(24, 64, 25, 60));
	entity.localScale = 2.53f;
	entity.sprite.texture = texture;

	CHECK(entity.name == "scalable test entity");
	CHECK(entity.rect.x == 24);
	CHECK(entity.rect.y == 64);
	CHECK(entity.rect.w == 25);
	CHECK(entity.rect.h == 60);
	CHECK(entity.angle == 0);
	CHECK(entity.sprite.texture.sdlTexture == texture.sdlTexture);
	CHECK(entity.localScale == 2.53f);
}



Birb2D::Font getTestFont()
{
	//Birb2D::RenderWindow window("Test window", 1280, 720, 60);
	SDL_Color color = {0, 0, 0, 0};
	Debug::Log("Getting test font...");
	Birb2D::Font font("../res/fonts/manaspace/manaspc.ttf", color, 32);
	//window.cleanUp();

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

TEST_CASE("entity with text")
{
	Debug::Log("Getting test font...");
	Birb2D::Font font = getTestFont();
	Birb2D::Entity text_entity("test text", Vector2f(15, 45));
	text_entity.text = Birb2D::Entity::Text("Testing... :)", font);

	CHECK(text_entity.name == "test text");
	CHECK(text_entity.text.value == "Testing... :)");
	CHECK(text_entity.rect.x == 15);
	CHECK(text_entity.rect.y == 45);
	CHECK(text_entity.text.font.getTTFFont() == font.getTTFFont());
}


TEST_CASE("change the angle of an entity")
{
	Birb2D::Texture texture;
	Birb2D::Entity entity("test entity", Rect(0, 0, 10, 10));
	entity.angle = 34.45f;

	CHECK_FALSE(entity.angle == 0);
	CHECK(entity.angle == 34.45f);
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

void ButtonTestMethod()
{
	Debug::Log("Buttons are working!");
}

TEST_CASE("Button widget")
{
	Debug::Log("Creating the window for button test...");
	Birb2D::RenderWindow window("Test window", 1280, 720, 240);
	Debug::Log("Window created! Getting test font...");
	Birb2D::Font font = getTestFont();
	Debug::Log("Test font got successfully");
	Birb2D::Widgets::Button testButton(window, Rect(5, 10, 150, 45), Colors::Black, "Test text", font, ButtonTestMethod, 0);
	Birb2D::Texture textTex = testButton.getEntity().sprite.texture;

	CHECK(testButton.getEntity().rect.x == 5 + 3);
	CHECK(testButton.getEntity().rect.y == 10 + 3);
	CHECK(testButton.getEntity().rect.w == textTex.dimensions.x - 3);
	CHECK(testButton.getEntity().rect.h == textTex.dimensions.y - 3);
	CHECK(textTex.dimensions.x != 0);
	CHECK(textTex.dimensions.y != 0);
	CHECK(testButton.getEntity().anchor.x == 0);
	CHECK(testButton.getEntity().anchor.y == 0);
}
