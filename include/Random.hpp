#pragma once

#ifndef DISTCC
#include "STD.hpp"
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
	};
}
