#pragma once

#include "STD.hpp"

namespace Birb
{
	namespace Filesystem
	{
		/* Directories */
		namespace Directory
		{
			void Create(const std::string& dpath); ///< Creates a new directory to given path
			void Remove(const std::string& dpath); ///< Removes a directory at given path
			bool Exists(const std::string& dpath); ///< Check if path points to a directory and it exists
		}

		/* Files */
		namespace File
		{
			void CreateEmpty(const std::string& fpath); ///< Creates an empty file to given path if the file doesn't exist already
			void Remove(const std::string& fpath); ///< Removes a file at given path if it exists
			bool Exists(const std::string& fpath); ///< Check if path points to a file and it exists

			std::string Read(const std::string& fpath); ///< Read file contents
			bool Write(const std::string& fpath, const std::string& content, const bool& overwrite = true); ///< Write text to a file. Returns true if successful
		}
	}
}
