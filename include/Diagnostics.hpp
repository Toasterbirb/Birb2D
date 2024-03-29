#pragma once

#include "Graphs.hpp"
#include "Timestep.hpp"

/* Diagnostics related headers */
#include "FrametimeGraph.hpp"

namespace Birb
{
	namespace Diagnostics
	{
		/// Boolean toggles for debugging features. Some can clutter the console output
		/// quite a bit, so be careful
        struct Debugging
        {
            static inline bool Buttons 			= false;
			static inline bool InitMessages		= false;
			static inline bool AssetLoading 	= false;

			struct Overlays
			{
				static inline bool ResourceMonitor 	= false;
			};
        };

	}
}
