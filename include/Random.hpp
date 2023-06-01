#pragma once

#ifndef DISTCC
#include "STD.hpp"
#else
#include <vector>
#endif


namespace Birb
{
	class Random
	{
	public:
		int RandomInt(int min, int max);
		float RandomFloat(float min, float max );

		/// Shuffles an array of any type
		template<typename T>
		static void ShuffleArray(T* values, int size)
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

		/// Shuffles a vector of any type
		template<typename T>
		static void ShuffleVector(std::vector<T>& values)
		{
			Random rand;
			size_t newIndex;
			T placeHolder;
			for (size_t i = 0; i < values.size(); ++i)
			{
				newIndex = rand.RandomInt(0, values.size() - 1);
				if (newIndex != i)
				{
					placeHolder = values[i];
					values[i] = values[newIndex];
					values[newIndex] = placeHolder;
				}
			}
		}
	};
}
