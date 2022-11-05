#include "Filesystem.hpp"
#include "Logger.hpp"

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

				std::string file_contents;
				char c;
				while (file.good())
				{
					c = file.get();
					file_contents += c;
				}

				/* Fix the null terminator */
				file_contents.erase(file_contents.size() - 1, 1);

				file.close();
				return file_contents;
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
		}
	}
}
