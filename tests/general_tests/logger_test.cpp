#include "doctest.h"
#include "Logger.hpp"
#include <filesystem>

using namespace Birb;

namespace BirbTest
{
	TEST_CASE("Logging")
	{
		std::cout << "There should be 4 different log messages showing up shortly..." << std::endl;
		CHECK_NOTHROW(Debug::Log("Log (this is only a test)"));
		CHECK_NOTHROW(Debug::Log("Log (this is only a test)", Birb::Debug::log));
		CHECK_NOTHROW(Debug::Log("Warning (this is only a test)", Birb::Debug::warning));
		CHECK_NOTHROW(Debug::Log("Error (this is only a test)", Birb::Debug::error));
		CHECK_NOTHROW(Debug::Log("Fixme (this is only a test)", Birb::Debug::fixme));
	}
}
