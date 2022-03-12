#pragma once

#include <string>

namespace Birb
{
	class Random
	{
	public:
		Random();

		static int RandomInt(const int& min, const int& max);
		static float RandomFloat(const float& min, const float& max );

		static void ShuffleArray(int* values, const int& size); ///< Shuffles an array of integers
		static void ShuffleArray(float* values, const int& size); ///< Shuffles an array of floats
		static void ShuffleArray(double* values, const int& size); ///< Shuffles an array of doubles
		static void ShuffleArray(std::string* values, const int& size); ///< Shuffles an array of strings
	};
}
