#include "Transition.hpp"
#include "Values.hpp"

namespace Birb
{
	BaseTransition::BaseTransition()
	{
		assert(("Alpha blending is required for transitions", Global::RenderVars::AlphaBlendingEnabled == true));
	}

	BaseTransition::~BaseTransition() {}
}
