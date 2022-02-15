#pragma once
#include <string>

namespace Birb
{
	namespace Filesystem
	{
		/* Directories */
		namespace Directory
		{
			void Create(std::string dpath); ///< Creates a new directory to given path
			void Remove(std::string dpath); ///< Removes a directory at given path
			bool Exists(std::string dpath); ///< Check if path points to a directory and it exists
		}

		/* Files */
		namespace File
		{
			void CreateEmpty(std::string fpath); ///< Creates an empty file to given path if the file doesn't exist already
			void Remove(std::string fpath); ///< Removes a file at given path if it exists
			bool Exists(std::string fpath); ///< Check if path points to a file and it exists

			std::string Read(std::string fpath); ///< Read file contents
			bool Write(std::string fpath, std::string content, bool overwrite = true); ///< Write text to a file. Returns true if successful
		}
	}
}
