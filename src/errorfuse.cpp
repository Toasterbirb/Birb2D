#include "Diagnostics.hpp"
#include "ErrorFuse.hpp"
#include "Logger.hpp"

namespace Birb
{
	ErrorFuse::ErrorFuse()
	:error_fuse(false) {}

	void ErrorFuse::BlowErrorFuse(const std::string& message)
	{
		error_fuse = true;

		if (Diagnostics::Debugging::FuseDebug)
			Debug::Log("Error fuse got triggered! Message: " + message, Debug::warning);
	}

	bool ErrorFuse::ErrorFuseStatus() const
	{
		return error_fuse;
	}
}
