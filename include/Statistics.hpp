#pragma once

#include "SceneObject.hpp"
namespace Birb
{
	namespace Diagnostics
	{
		/// Draw a text overlay that shows some
		/// runtime performance statistics. Due to the nature of
		/// some statistics, this feature is only available on Linux
		class Statistics : public SceneObject
		{
		public:
			Statistics();

		private:
			void RenderFunc() override;
			void SetPos(const Vector2& delta) override;
		};
	}
}
