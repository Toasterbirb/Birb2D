#include <filesystem>
#include <fstream>
#include "Filesystem.hpp"
#include "Logger.hpp"
#include "doctest.h"

namespace Birb
{
	namespace Filesystem
	{
		namespace Directory
		{
			void Create(const std::string& dpath)
			{
				std::filesystem::create_directories(dpath);
			}

			void Remove(const std::string& dpath)
			{
				if (std::filesystem::is_directory(dpath))
					std::filesystem::remove(dpath);
			}

			bool Exists(const std::string& dpath)
			{
				return (std::filesystem::exists(dpath) && std::filesystem::is_directory(dpath));
			}

			TEST_CASE("Filesystem directories")
			{
				Birb::Debug::Log("Starting filesystem checks. There will be a few errors and they are deliberate");
				std::string directoryPath = "./testing_directory";

				/* Create a directory and check if it exists */
				Birb::Filesystem::Directory::Create(directoryPath);
				CHECK(Birb::Filesystem::Directory::Exists(directoryPath));

				/* Remove the previously created directory and check if its gone */
				Birb::Filesystem::Directory::Remove(directoryPath);
				CHECK_FALSE(Birb::Filesystem::Directory::Exists(directoryPath));
			}
		}

		namespace File
		{
			void CreateEmpty(const std::string& fpath)
			{
				if (!std::filesystem::exists(fpath))
					std::ofstream output(fpath);
				else
					Debug::Log("File '" + fpath + "' exists already. Not overwriting it...", Debug::Type::warning);
			}

			void Remove(const std::string& fpath)
			{
				if (Exists(fpath))
					std::filesystem::remove(fpath);
				else
					Debug::Log("Tried to remove file '" + fpath + "' even though it doesn't even exist", Debug::Type::warning);
			}

			bool Exists(const std::string& fpath)
			{
				return (std::filesystem::exists(fpath) && std::filesystem::is_regular_file(fpath));
			}

			std::string Read(const std::string& fpath)
			{
				/* Make sure the file exists */
				if (!Exists(fpath))
				{
					Debug::Log("File '" + fpath + "' doesn't exist. Can't read it.", Debug::Type::error);
					return "";
				}

				std::ifstream file;
				file.open(fpath, std::ios::in);
				
				std::string fileContents;
				file >> fileContents;

				file.close();
				return fileContents;
			}

			bool Write(const std::string& fpath, const std::string& content, const bool& overwrite)
			{
				/* Check if a file exists if overwrite protection is enabled */
				if (!overwrite && Exists(fpath))
				{
					Debug::Log("File '" + fpath + "' exists already. Not going to overwrite it...", Debug::Type::warning); 
					return false;
				}
				else if (std::filesystem::is_directory(fpath))
				{
					Debug::Log("'" + fpath + "' is a directory. Can't write to it as a file", Debug::Type::error);
					return false;
				}

				std::ofstream file;
				file.open(fpath);
				file << content;
				file.close();
				return true;
			}

			TEST_CASE("Filesystem files")
			{
				std::string filepath = "./testing_file";

				/* Create an empty file and check if it exists */
				Birb::Filesystem::File::CreateEmpty(filepath);
				CHECK(Birb::Filesystem::File::Exists(filepath));

				/* Try to write into the file and read its contents */
				CHECK(Birb::Filesystem::File::Write(filepath, "test"));
				CHECK(Birb::Filesystem::File::Read(filepath) == "test");

				/* Test overwrite protection */
				CHECK_FALSE(Birb::Filesystem::File::Write(filepath, "testing testing", false));
				CHECK(Birb::Filesystem::File::Read(filepath) == "test");

				/* Remove the previously created file and check if its gone */
				Birb::Filesystem::File::Remove(filepath);
				CHECK_FALSE(Birb::Filesystem::File::Exists(filepath));

				/* Try reading from non-existant file */
				CHECK(Birb::Filesystem::File::Read(filepath) == "");

				/* Create a directory and try writing to it */
				Birb::Filesystem::Directory::Create(filepath);
				CHECK_FALSE(Birb::Filesystem::File::Write(filepath, "test"));
				Birb::Filesystem::Directory::Remove(filepath);
			}
		}
	}
}
