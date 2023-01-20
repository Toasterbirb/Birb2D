#include "ErrorFuse.hpp"

namespace Birb
{
	ErrorFuse::ErrorFuse()
	:error_fuse(false) {}

	void ErrorFuse::BlowErrorFuse()
	{
		error_fuse = true;
	}

	bool ErrorFuse::ErrorFuseStatus() const
	{
		return error_fuse;
	}
}
