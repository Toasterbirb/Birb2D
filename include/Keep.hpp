#pragma once
#include "AppInfo.hpp"
#include "STD.hpp"
#include "json.hpp"

namespace Birb
{
	class Keep
	{
	public:
		/// Open a keep vault from a default file path
		/// that is derived from the application name
		Keep(const ApplicationInfo& app_info);

		/// Open a keep vault from custom path
		Keep(const std::string& custom_path);

		/// Clear all vaults or some specific vault
		void Wipe(const std::string& vault = "");

		/// Save everything to a datafile
		void Save() const;

		template<typename T>
		T GetValue(const std::string& key, const std::string& vault, const T& default_value)
		{
			if (!json_data[vault][key].empty())
				return json_data[vault][key];

			return default_value;
		}

		template<typename T>
		T GetValue(const std::string& key, const std::string& vault)
		{
			return json_data[vault][key];
		}

		template<typename T>
		void SetValue(const std::string& key, const T& value, const std::string& vault)
		{
			json_data[vault][key] = value;
		}

	private:
		nlohmann::json json_data;
		std::string data_path;
	};
}
