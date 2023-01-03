#include "Keep.hpp"
#include "AppInfo.hpp"
#include "Filesystem.hpp"
#include "STD.hpp"

#define VAULT_FILE "vault.json"

namespace Birb
{
	Keep::Keep(const ApplicationInfo& app_info)
	{
		/* Open the vault directory */
		data_path = app_info.locate_data_path() + "/" + VAULT_FILE;

		/* Read the json file in if it exists. Otherwise just
		 * create a default empty file */
		if (Birb::Filesystem::File::Exists(data_path))
		{
			json_data = nlohmann::json::parse(Birb::Filesystem::File::Read(data_path));
		}
		else
		{
			std::ofstream file(data_path);
			file << std::setw(4) << json_data << std::endl;
		}
	}

	void Keep::Wipe(const std::string& vault)
	{
		if (vault.empty())
			json_data.clear();
		else
			json_data[vault].clear();
	}

	void Keep::Save() const
	{
		std::ofstream file(data_path);
		file << std::setw(4) << json_data << std::endl;
	}
}
