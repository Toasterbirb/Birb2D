#pragma once


namespace Birb
{
	/// A "fuse" that can be blown if an error occurs.
	/// This is useful for automated testing purposes, but also debugging
	class ErrorFuse
	{
	public:
		ErrorFuse();

		/// Blow the error fuse in this object. This function is mainly used for
		/// automated testing purposes
		void BlowErrorFuse();

		/// Check the status of the error fuse.
		/// If this function returns true, something has gone
		/// wrong with this object during its lifespan
		bool ErrorFuseStatus() const;

	private:
		bool error_fuse = false;
	};
}
