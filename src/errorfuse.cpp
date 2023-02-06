#include "Diagnostics.hpp"
#include "ErrorFuse.hpp"
#include "Logger.hpp"

namespace Birb
{
	ErrorFuse::ErrorFuse()
	:error_fuse(false) {}

	void ErrorFuse::BlowErrorFuse()
	{
		error_fuse = true;

		if (Diagnostics::Debugging::FuseDebug)
			Debug::Log("Error fuse got triggered! This could be an indicator for an engine bug :(", Debug::warning);
	}

	bool ErrorFuse::ErrorFuseStatus() const
	{
		return error_fuse;
	}
}
