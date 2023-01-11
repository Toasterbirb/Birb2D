#pragma once

namespace Birb
{
	/// Monitor for changes in a value. Useful for keeping track
	/// of changes between input() and update()
	template<typename T>
	class var
	{
	public:
		var(const T& initial_value)
		{
			current_value	= initial_value;
			old_value 		= initial_value;
		}

		void operator=(const T& other)
		{
			this->current_value = other;
		}

		bool operator==(const T& other) const
		{
			return (this->current_value == other);
		}

		/// Reference to the current value
		T& value()
		{
			return current_value;
		}

		/// Check if the value has changed after the last time
		/// this function was called
		bool HasChanged()
		{
			bool result = !(current_value == old_value);
			old_value = current_value;
			return result;
		}

	private:
		T current_value;
		T old_value;
	};
}
