#ifndef DOCTEST_CONFIG_DISABLE
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 
#endif

#include "doctest.h"
#include "Entity.hpp"
#include "Utils.hpp"
#include "Math.hpp"
#include "Audio.hpp"
#include "Values.hpp"
#include "Logger.hpp"
#include "Renderwindow.hpp"
#include "Filesystem.hpp"


TEST_CASE("Random int")
{
	/* Make sure that the functions return a different value every time */
	Birb::utils::InitRandomGen();

	int valueCount = 50;
	int values[50];
	for (int i = 0; i < valueCount; i++)
		values[i] = Birb::utils::randomInt(0, 10);

	/* Check if all of the values were the same */
	int firstValue = values[0];
	bool differentValueFound = false;
	for (int i = 1; i < valueCount; i++)
	{
		//std::cout << "[" << i << "] Randon value: " << values[i] << std::endl;
		if (values[i] != firstValue)
		{
			differentValueFound = true;
			//break;
		}
	}

	CHECK(differentValueFound);
}

TEST_CASE("logging")
{
	CHECK_NOTHROW(Birb::Debug::Log("Log (this is only a test)"));
	CHECK_NOTHROW(Birb::Debug::Log("Log (this is only a test)", Birb::Debug::log));
	CHECK_NOTHROW(Birb::Debug::Log("Warning (this is only a test)", Birb::Debug::warning));
	CHECK_NOTHROW(Birb::Debug::Log("Error (this is only a test)", Birb::Debug::error));
}

TEST_CASE("window and rendering functions")
{
	Birb::Window window("Title", Birb::Vector2int(1280, 720), 60, false);
	SDL_Texture* texture 	= Birb::Resources::LoadTexture("/home/toasterbirb/git/birb2d/res/textures/giga_stretch.png");
	TTF_Font* font 			= Birb::Resources::LoadFont("/home/toasterbirb/git/birb2d/res/fonts/freefont/FreeMonoBold.ttf", 32);

	CHECK(window.win_title == "Title");
	CHECK(window.window_dimensions.x == 1280);
	CHECK(window.window_dimensions.y == 720);
	CHECK(window.refresh_rate == 60);
	CHECK(window.win 		!= NULL);
	CHECK(window.renderer 	!= NULL);
	CHECK(texture 	!= nullptr);
	CHECK(font 		!= nullptr);

	CHECK_NOTHROW(window.Clear());
	CHECK_NOTHROW(window.Display());
	CHECK_NOTHROW(window.Cleanup());

	SDL_Quit();
}

// ### Math stuff and other utilities ###
TEST_CASE("Default Vector2f")
{
    Birb::Vector2f vector;
    CHECK(vector.x == 0);
    CHECK(vector.y == 0);
}

TEST_CASE("Vector2f with arguments")
{
    CHECK(Birb::Vector2f(1, 4).x == 1);
    CHECK(Birb::Vector2f(1, 4).y == 4);
    CHECK(Birb::Vector2f(1.53f, 5.21f).x == 1.53f);
    CHECK(Birb::Vector2f(1.53f, 5.21f).y == 5.21f);
}

TEST_CASE("Default Vector2int")
{
    Birb::Vector2int vector;
    CHECK(vector.x == 0);
    CHECK(vector.y == 0);
}

TEST_CASE("Vector2int with arguments")
{
    CHECK(Birb::Vector2int(1, 4).x == 1);
    CHECK(Birb::Vector2int(1, 4).y == 4);
    CHECK(Birb::Vector2int(1.53f, 5.21f).x == 2);
    CHECK(Birb::Vector2int(1.53f, 5.21f).y == 5);
}

TEST_CASE("Default Vector3f")
{
	Birb::Vector3f vector;
    CHECK(vector.x == 0);
    CHECK(vector.y == 0);
    CHECK(vector.z == 0);
}

TEST_CASE("Vector3f with arguments")
{
    CHECK(Birb::Vector3f(1, 4, 2).x == 1);
    CHECK(Birb::Vector3f(1, 4, 2).y == 4);
    CHECK(Birb::Vector3f(1, 4, 2).z == 2);
    CHECK(Birb::Vector3f(1.53f, 5.21f, 2.45f).x == 1.53f);
    CHECK(Birb::Vector3f(1.53f, 5.21f, 2.45f).y == 5.21f);
    CHECK(Birb::Vector3f(1.53f, 5.21f, 2.45f).z == 2.45f);
}

TEST_CASE("Default Vector3int")
{
	Birb::Vector3int vector;
    CHECK(vector.x == 0);
    CHECK(vector.y == 0);
    CHECK(vector.z == 0);
}

TEST_CASE("Vector3int with arguments")
{
    CHECK(Birb::Vector3int(1, 4, 2).x == 1);
    CHECK(Birb::Vector3int(1, 4, 2).y == 4);
    CHECK(Birb::Vector3int(1, 4, 2).z == 2);
    CHECK(Birb::Vector3int(1.53f, 5.21f, 2.45f).x == 2);
    CHECK(Birb::Vector3int(1.53f, 5.21f, 2.45f).y == 5);
    CHECK(Birb::Vector3int(1.53f, 5.21f, 2.45f).z == 2);
}

TEST_CASE("Distance calculation with 2D vectors")
{
	Birb::Vector2f pointAf(1.0f, 1.0f);
	Birb::Vector2f pointBf(8.0f, 3.0f);

	Birb::Vector2int pointAint(1, 1);
	Birb::Vector2int pointBint(8, 3);

	CHECK(Birb::Math::VectorDistance(pointAf, pointBf) == 7.2801098892805f);
	CHECK(Birb::Math::VectorDistance(pointAint, pointBint) == 7.2801098892805f);
}

TEST_CASE("Distance calculation with 3D vectors")
{
	Birb::Vector3f pointAf(1.0f, 1.0f, 1.0f);
	Birb::Vector3f pointBf(8.0f, 3.0f, 2.0f);

	Birb::Vector3int pointAint(1, 1, 1);
	Birb::Vector3int pointBint(8, 3, 2);

	CHECK(std::roundf(Birb::Math::VectorDistance(pointAf, pointBf)) == std::roundf(7.3484792283495));
	CHECK(std::roundf(Birb::Math::VectorDistance(pointAint, pointBint)) == std::roundf(7.3484692283495));
}

TEST_CASE("Lerping / interpolation with integers")
{
	int a = 1;
	int b = 10;

	CHECK(Birb::Math::Lerp(a, b, 0) == 1);
	CHECK(Birb::Math::Lerp(a, b, 0.5) == 6);
	CHECK(Birb::Math::Lerp(a, b, 0.75) == 8);
	CHECK(Birb::Math::Lerp(a, b, 1) == 10);
}

TEST_CASE("Lerping / interpolation with floats")
{
	float a = 1;
	float b = 3;

	CHECK(Birb::Math::Lerp(a, b, 0) == 1);
	CHECK(Birb::Math::Lerp(a, b, 0.25) == 1.5f);
	CHECK(Birb::Math::Lerp(a, b, 0.5) == 2);
	CHECK(Birb::Math::Lerp(a, b, 1) == 3);
}

TEST_CASE("Lerping / interpolation with 2D float vectors")
{
	Birb::Vector2f vecAf = { 1.0f, 1.0f };
	Birb::Vector2f vecBf = { 4.0f, 2.0f };

	CHECK(Birb::Math::Lerp(vecAf, vecBf, 0) == Birb::Vector2f(1, 1));
	CHECK(Birb::Math::Lerp(vecAf, vecBf, 0.5) == Birb::Vector2f(2.5, 1.5));
	CHECK(Birb::Math::Lerp(vecAf, vecBf, 0.75) == Birb::Vector2f(3.25, 1.75));
	CHECK(Birb::Math::Lerp(vecAf, vecBf, 1) == Birb::Vector2f(4, 2));
}

TEST_CASE("Lerping / interpolation with 2D integer vectors")
{
	Birb::Vector2int vecAint = { 10, 10 };
	Birb::Vector2int vecBint = { 40, 20 };

	CHECK(Birb::Math::Lerp(vecAint, vecBint, 0) == Birb::Vector2int(10, 10));
	CHECK(Birb::Math::Lerp(vecAint, vecBint, 0.5) == Birb::Vector2int(25, 15));
	CHECK(Birb::Math::Lerp(vecAint, vecBint, 0.75) == Birb::Vector2int(33, 18));
	CHECK(Birb::Math::Lerp(vecAint, vecBint, 1) == Birb::Vector2int(40, 20));
}

TEST_CASE("Lerping / interpolation with 3D float vectors")
{
	Birb::Vector3f vecAf = { 1.0f, 1.0f, 1.0f };
	Birb::Vector3f vecBf = { 4.0f, 2.0f, 3.0f };

	CHECK(Birb::Math::Lerp(vecAf, vecBf, 0) == Birb::Vector3f(1, 1, 1));
	CHECK(Birb::Math::Lerp(vecAf, vecBf, 0.5) == Birb::Vector3f(2.5, 1.5, 2));
	CHECK(Birb::Math::Lerp(vecAf, vecBf, 0.75) == Birb::Vector3f(3.25, 1.75, 2.5));
	CHECK(Birb::Math::Lerp(vecAf, vecBf, 1) == Birb::Vector3f(4, 2, 3));
}

TEST_CASE("Lerping / interpolation with 3D integer vectors")
{
	Birb::Vector3int vecAint = { 10, 10, 10 };
	Birb::Vector3int vecBint = { 40, 20, 30 };

	CHECK(Birb::Math::Lerp(vecAint, vecBint, 0) == Birb::Vector3int(10, 10, 10));
	CHECK(Birb::Math::Lerp(vecAint, vecBint, 0.5) == Birb::Vector3int(25, 15, 20));
	CHECK(Birb::Math::Lerp(vecAint, vecBint, 0.75) == Birb::Vector3int(33, 18, 25));
	CHECK(Birb::Math::Lerp(vecAint, vecBint, 1) == Birb::Vector3int(40, 20, 30));
}

TEST_CASE("Calculate the centerpoint between two 1D floats")
{
	float a = 0;
	float b = 10;

	CHECK(Birb::Math::CenterPoint(a, b) == 5);
}

TEST_CASE("Calculate the centerpoint between two 2D vectors")
{
	Birb::Vector2f pointAf(1.0f, 1.0f);
	Birb::Vector2f pointBf(8.0f, 3.0f);

	Birb::Vector2int pointAint(1, 1);
	Birb::Vector2int pointBint(8, 3);

	Birb::Vector2f resultf = Birb::Math::CenterPoint(pointAf, pointBf);
	Birb::Vector2f resultint = Birb::Math::CenterPoint(pointAint, pointBint);
	Birb::Vector2f expectedResult(4.5f, 2.0f);

	CHECK(resultf == expectedResult);
	CHECK(resultint == expectedResult);
}

TEST_CASE("Calculate the centerpoint between two 3D vectors")
{
	Birb::Vector3f pointAf(1.0f, 1.0f, 1.0f);
	Birb::Vector3f pointBf(8.0f, 3.0f, 2.0f);

	Birb::Vector3int pointAint(1, 1, 1);
	Birb::Vector3int pointBint(8, 3, 2);

	Birb::Vector3f resultf = Birb::Math::CenterPoint(pointAf, pointBf);
	Birb::Vector3f resultint = Birb::Math::CenterPoint(pointAint, pointBint);
	Birb::Vector3f expectedResult(4.5f, 2.0f, 1.5f);

	CHECK(resultf == expectedResult);
	CHECK(resultint == expectedResult);
}

TEST_CASE("Rounding with specified accuracy")
{
	double value1 = 0.013333333;
	float value2 = 0.017777777;

	CHECK(Birb::Math::Round(value1, 6) == 0.013333);
	CHECK(Birb::Math::Round(value1, 3) == 0.013);
	CHECK(Birb::Math::Round(value1, 2) == 0.01);

	CHECK(Birb::Math::Round(value2, 6) == 0.017778);
	CHECK(Birb::Math::Round(value2, 3) == 0.018);
	CHECK(Birb::Math::Round(value2, 2) == 0.02);
}

/* End of math things */

TEST_CASE("Vector2f operator overloads")
{
	Birb::Vector2f vecA(1.0f, 1.5f);
	Birb::Vector2f vecB(2.0f, 3.2f);

	CHECK(vecA + vecB == Birb::Vector2f(3.0f, 4.7f));
	CHECK(vecA - vecB == Birb::Vector2f(-1.0f, -1.7f));
	CHECK(vecA * vecB == Birb::Vector2f(2.0f, 4.8f));
	CHECK(vecA / vecB == Birb::Vector2f(0.5f, 0.46875f));
}

TEST_CASE("Vector2int operator overloads")
{
	Birb::Vector2int vecA(4, 2);
	Birb::Vector2int vecB(2, 3);

	CHECK(vecA + vecB == Birb::Vector2int(6, 5));
	CHECK(vecA - vecB == Birb::Vector2int(2, -1));
	CHECK(vecA * vecB == Birb::Vector2int(8, 6));
	CHECK(vecA / vecB == Birb::Vector2int(2, 1));
}

TEST_CASE("Vector3f operator overloads")
{
	Birb::Vector3f vecA(1.0f, 1.5f, 0.2f);
	Birb::Vector3f vecB(2.0f, 3.2f, 2.0f);

	CHECK(vecA + vecB == Birb::Vector3f(3.0f, 4.7f, 2.2f));
	CHECK(vecA - vecB == Birb::Vector3f(-1.0f, -1.7f, -1.8f));
	CHECK(vecA * vecB == Birb::Vector3f(2.0f, 4.8f, 0.4f));
	CHECK(vecA / vecB == Birb::Vector3f(0.5f, 0.468750f, 0.1f));
}

TEST_CASE("Vector3int operator overloads")
{
	Birb::Vector3int vecA(4, 6, 5);
	Birb::Vector3int vecB(2, 3, 2);

	CHECK(vecA + vecB == Birb::Vector3int(6, 9, 7));
	CHECK(vecA - vecB == Birb::Vector3int(2, 3, 3));
	CHECK(vecA * vecB == Birb::Vector3int(8, 18, 10));
	CHECK(vecA / vecB == Birb::Vector3int(2, 2, 3));
}

TEST_CASE("Default Rect")
{
	Birb::Rect defaultRect;
    CHECK(defaultRect.x == 0);
    CHECK(defaultRect.y == 0);
    CHECK(defaultRect.w == 0);
    CHECK(defaultRect.h == 0);

}

TEST_CASE("Rect with arguments")
{
	Birb::Rect customRect(10.54, 20, 30.234, 40.6668);
    CHECK(customRect.x == 10.54f);
    CHECK(customRect.y == 20);
    CHECK(customRect.w == 30.234f);
    CHECK(customRect.h == 40.6668f);
}

TEST_CASE("Rect with rounded values (integer)")
{
	Birb::Rect customRect(10.54, 20, 30.234, 40.6668);
    Birb::Rect roundedRect = customRect.getInt();

    CHECK(roundedRect.x == 11);
    CHECK(roundedRect.y == 20);
    CHECK(roundedRect.w == 30);
    CHECK(roundedRect.h == 41);
}

TEST_CASE("Timer stop test")
{
	Birb::Debug::Log("Running timer tests, this might take a moment...");
	Birb::Timer timer;
	timer.Start();
	SDL_Delay(1000);
	timer.Stop();

	CHECK(timer.ElapsedSeconds() == 1.00);

	/* Make sure the timer actually stops after stopping it */
	SDL_Delay(500);
	CHECK(timer.ElapsedSeconds() == 1.00);
}

TEST_CASE("Timer accuracy test")
{
	Birb::Timer timer;
	timer.Start();
	SDL_Delay(123);
	timer.Stop();

	CHECK(timer.ElapsedMilliseconds() == 123);
}

TEST_CASE("Filesystem directories")
{
	std::string directoryPath = "./testing_directory";

	/* Create a directory and check if it exists */
	Birb::Filesystem::Directory::Create(directoryPath);
	CHECK(Birb::Filesystem::Directory::Exists(directoryPath));

	/* Remove the previously created directory and check if its gone */
	Birb::Filesystem::Directory::Remove(directoryPath);
	CHECK_FALSE(Birb::Filesystem::Directory::Exists(directoryPath));
}

TEST_CASE("Filesystem files")
{
	std::string filepath = "./testing_file";

	/* Create an empty file and check if it exists */
	Birb::Filesystem::File::CreateEmpty(filepath);
	CHECK(Birb::Filesystem::File::Exists(filepath));

	/* Try to write into the file and read its contents */
	CHECK(Birb::Filesystem::File::Write(filepath, "test"));
	CHECK(Birb::Filesystem::File::Read(filepath) == "test");

	/* Test overwrite protection */
	CHECK_FALSE(Birb::Filesystem::File::Write(filepath, "testing testing", false));
	CHECK(Birb::Filesystem::File::Read(filepath) == "test");

	/* Remove the previously created file and check if its gone */
	Birb::Filesystem::File::Remove(filepath);
	CHECK_FALSE(Birb::Filesystem::File::Exists(filepath));

	/* Try reading from non-existant file */
	CHECK(Birb::Filesystem::File::Read(filepath) == "");

	/* Create a directory and try writing to it */
	Birb::Filesystem::Directory::Create(filepath);
	CHECK_FALSE(Birb::Filesystem::File::Write(filepath, "test"));
	Birb::Filesystem::Directory::Remove(filepath);
}
