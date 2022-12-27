#include "Filesystem.hpp"
#include "Logger.hpp"
#include "doctest.h"

namespace Birb
{
	namespace Filesystem
	{
		namespace Directory
		{
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
			TEST_CASE("Filesystem files")
			{
				std::string filepath = "./testing_file";
				std::string test_text = "Asperiores ea iste amet ex quo itaque quae. Qui quia veritatis consequatur et quasi impedit doloremque et. Sequi non reprehenderit earum magni at consequuntur et.";

				/* Create an empty file and check if it exists */
				Birb::Filesystem::File::CreateEmpty(filepath);
				CHECK(Birb::Filesystem::File::Exists(filepath));

				/* Try to write into the file and read its contents */
				CHECK(Birb::Filesystem::File::Write(filepath, test_text));
				CHECK(Birb::Filesystem::File::Read(filepath) == test_text);

				/* Test overwrite protection */
				CHECK_FALSE(Birb::Filesystem::File::Write(filepath, "testing testing", false));
				CHECK(Birb::Filesystem::File::Read(filepath) == test_text);

				/* Remove the previously created file and check if its gone */
				Birb::Filesystem::File::Remove(filepath);
				CHECK_FALSE(Birb::Filesystem::File::Exists(filepath));

				/* Try reading from non-existant file */
				CHECK(Birb::Filesystem::File::Read(filepath) == "");

				/* Create a directory and try writing to it */
				Birb::Filesystem::Directory::Create(filepath);
				CHECK_FALSE(Birb::Filesystem::File::Write(filepath, test_text));
				Birb::Filesystem::Directory::Remove(filepath);
			}
		}
	}
}
