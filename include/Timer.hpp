#include <chrono>
#include <ctime>
#include <cmath>
#include <string>

namespace Birb
{
	/// Class for timing things. Accurate down to milliseconds
	class Timer
	{
	public:
		void Start();
		void Stop();
		double ElapsedMilliseconds();
		double ElapsedSeconds();
		double ElapsedMinutes();
		double ElapsedHours();

		double CalcSeconds(double mills); 	///< Converts milliseconds into seconds
		double CalcMinutes(double mills); 	///< Converts milliseconds into minutes
		double CalcHours(double mills); 	///< Converts milliseconds into hours
		
		std::string DigitalFormat(); 		///< Prints the current elapsed time in digital format (00:00:00:000)
		std::string SplitDigitalFormat(double previousmills /**< [in] elapsed milliseconds of the previous split */); ///< Used for calculating digital time for a split during timing
		bool running = false;

	private:
		std::chrono::time_point<std::chrono::steady_clock> startTime;
		std::chrono::time_point<std::chrono::steady_clock> endTime;
	};
}
