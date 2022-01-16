#include <chrono>
#include <ctime>
#include <cmath>
#include <string>

namespace Birb2D
{
	class Timer
	{
	public:
		void Start();
		void Stop();
		double ElapsedMilliseconds();
		double ElapsedSeconds();
		double ElapsedMinutes();
		double ElapsedHours();

		double CalcSeconds(double mills);
		double CalcMinutes(double mills);
		double CalcHours(double mills);
		
		std::string DigitalFormat();
		std::string SplitDigitalFormat(double previousmills);
		bool running = false;

	private:
		std::chrono::time_point<std::chrono::steady_clock> startTime;
		std::chrono::time_point<std::chrono::steady_clock> endTime;
	};
}
