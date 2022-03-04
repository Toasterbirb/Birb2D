#include "doctest.h"
#include "Values.hpp"

TEST_CASE("Locate resources")
{
	std::string ApplicationName = "Birb2D_engine";
	Birb::ApplicationInfo appInfo(ApplicationName);
	appInfo.LocateResources();

	CHECK(appInfo.AppName 		== ApplicationName);
	CHECK(appInfo.ResLocation 	== "./res");
}
