#pragma once

#include <random>
#include "STD.hpp"

namespace Birb
{
	class Random
	{
	public:
		int RandomInt(const int& min, const int& max);
		float RandomFloat(const float& min, const float& max );

		/// Shuffles an array of any time
		template<typename T>
		static void ShuffleArray(T* values, const int& size)
		{
			Random rand;
			int newIndex;
			T placeHolder;
			for (int i = 0; i < size; ++i)
			{
				newIndex = rand.RandomInt(0, size - 1);
				if (newIndex != i)
				{
					placeHolder = values[i];
					values[i] = values[newIndex];
					values[newIndex] = placeHolder;
				}
			}
		}

	private:
		std::random_device random_machine;
	};
}
