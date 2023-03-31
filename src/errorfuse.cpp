#include "Diagnostics.hpp"
#include "ErrorFuse.hpp"
#include "Logger.hpp"

namespace Birb
{
	ErrorFuse::ErrorFuse()
	:error_fuse(false) {}

	void ErrorFuse::__BlowErrorFuse(const char* file, int line)
	{
		error_fuse = true;

		if (Diagnostics::Debugging::FuseDebug)
			Debug::Log(std::string(file) + " : " + std::to_string(line), Debug::fixme);
	}

	bool ErrorFuse::ErrorFuseStatus() const
	{
		return error_fuse;
	}
}
