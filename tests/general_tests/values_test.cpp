#include "doctest.h"
#include "AppInfo.hpp"

TEST_CASE("Create ApplicationInfo instance")
{
	std::string ApplicationName = "Birb2D_engine";
	Birb::ApplicationInfo appInfo(ApplicationName);

	CHECK(appInfo.AppName 		== ApplicationName);
}
