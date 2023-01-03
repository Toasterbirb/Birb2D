#include "AppInfo.hpp"
#include "doctest.h"
#include "Keep.hpp"
#include <vector>

namespace Birb
{
	TEST_CASE("Get a value from a Keep vault")
	{
		ApplicationInfo app_info("test_game");
		Keep savegame(app_info);

		/* Nuke the keep vaults */
		savegame.Wipe();

		/* Test default values */
		int number = savegame.GetValue("number", "test_vault", 5);
		CHECK(number == 5);

		std::string text = savegame.GetValue<std::string>("text", "test_vault", "Hello world");
		CHECK(text == "Hello world");

		double double_floating_point_number = savegame.GetValue("double key", "test_vault", 5.1234);
		CHECK(double_floating_point_number == 5.1234);

		float float_floating_point_number = savegame.GetValue("double key", "test_vault", 5.1234f);
		CHECK(float_floating_point_number == 5.1234f);

		std::vector<int> list_of_numbers = savegame.GetValue("number_list", "list_test_vault", std::vector<int>());
		CHECK(list_of_numbers.size() == 0);
		list_of_numbers.push_back(3);
		list_of_numbers.push_back(6);

		/* Set some value */
		savegame.SetValue("number", 10, "test_vault");
		number = savegame.GetValue("number", "test_vault", 5);
		CHECK(number == 10);

		savegame.SetValue("number_list", list_of_numbers, "list_test_vault");

		/* Try to read a vector back into a variable */
		std::vector<int> another_list = savegame.GetValue<std::vector<int>>("number_list", "list_test_vault");
		CHECK(another_list[0] == 3);
		CHECK(another_list[1] == 6);
		CHECK(another_list.size() == 2);

		/* Save the values */
		savegame.Save();

		/* Re-open the savegame in another gaming session */
		Keep new_game_session_savegame(app_info);
		CHECK(new_game_session_savegame.GetValue<int>("number", "test_vault") == 10);
	}
}
