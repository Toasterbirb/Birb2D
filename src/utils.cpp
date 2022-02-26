#include "Utils.hpp"
#include "doctest.h"
#include "Logger.hpp"

namespace Birb
{
	Rect::Rect()
	:x(0.0f), y(0.0f), w(0.0f), h(0.0f)
	{}

	Rect::Rect(const float& p_x, const float& p_y, const float& p_w, const float& p_h)
	:x(p_x), y(p_y), w(p_w), h(p_h)
	{}

	Rect Rect::getInt()
	{
		Rect roundedRect;
		roundedRect.x = round(x);
		roundedRect.y = round(y);
		roundedRect.w = round(w);
		roundedRect.h = round(h);

		return roundedRect;
	}

	SDL_Rect Rect::getSDLRect() const
	{
		SDL_Rect sdlrect;
		sdlrect.h = h;
		sdlrect.w = w;
		sdlrect.x = x;
		sdlrect.y = y;
		return sdlrect;
	}

	/* Rect tests */
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
	/* End of tests */


	namespace utils
	{
		std::vector<Vector2int> SortPath(const Vector2int& startPoint, const std::vector<Vector2int>& points)
		{
			std::vector<Vector2int> result;
			Vector2int closestPoint;
			result.push_back(startPoint);

			for (int i = 0; i < (int)points.size(); i++)
			{
				/* Skip the point if its the start point */
				if (startPoint == points[i])
					continue;

				closestPoint = Birb::Math::FindClosestPoint(result[result.size() - 1], points, result);
				result.push_back(closestPoint);
			}

			return result;
		}

		TEST_CASE("Sort path with a startpoint")
		{
			std::vector<Birb::Vector2int> points = {
				Birb::Vector2int(0, 0),
				Birb::Vector2int(3, 3),
				Birb::Vector2int(1, 1),
				Birb::Vector2int(8, 9),
				Birb::Vector2int(6, 6),
			};

			Birb::Debug::Log("Sorting a path...");
			for (int i = 0; i < (int)points.size(); i++)
			{
				Birb::Debug::Log(points[i].print());
			}

			points = Birb::utils::SortPath(points[0], points);
			Birb::Debug::Log("----->");

			for (int i = 0; i < (int)points.size(); i++)
			{
				Birb::Debug::Log(points[i].print());
			}

			CHECK(points.size() == 5);
			CHECK(points[0] == Birb::Vector2int(0, 0));
			CHECK(points[1] == Birb::Vector2int(1, 1));
			CHECK(points[2] == Birb::Vector2int(3, 3));
			CHECK(points[3] == Birb::Vector2int(6, 6));
			CHECK(points[4] == Birb::Vector2int(8, 9));
		}
	}
}

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
