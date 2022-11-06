#include "Birb2D.hpp"
#include "STD.hpp"
#include "../../vendor/cppcodec/cppcodec/base64_rfc4648.hpp"

void PrintHelp()
{
	std::cout << "## Birb Asset Packer ##\n" <<
"This tool is used for packing Birb2D assets into a binary blob.\nThis should *in theory* speed up the game loading times and stuff by reducing unnecessary disk I/O. The binary blob is stored into a header file as base64, so that it can be directly included into the game binary. This way of packing the resources doesn't probably scale too well for bigger games, but should be fine for small games that don't have too many assets to load.\n" << std::endl;

	std::cout << "Usage: ./birb-asset-packer [path to resource zip file] [path to a header directory that gets included]" << std::endl;
}

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		PrintHelp();
		return 0;
	}

	if (argc != 3)
	{
		std::cout << "Missing args..." << std::endl;
		return 1;
	}

	std::string res_path = argv[1];
	std::string header_path = argv[2];

	/* Remove the last '/' from the header path in case there ise one */
	if (header_path[header_path.size() - 1] == '/')
		header_path.erase(header_path.size() - 1, 1);

	/* Add the final filename into the header_path */
	header_path = header_path + "/AssetBundle.hpp";

	std::vector<std::string> header_file;

	/* Add some boilerplate stuff into the headerfile */
	header_file.push_back("#pragma once");
	header_file.push_back("#define HEADER_ASSET");

	/* Read the zip file */
	std::ifstream zip_file;
	zip_file.open(res_path.c_str(), std::ios_base::in | std::ios_base::binary);
	if (!zip_file.is_open())
	{
		std::cout << "Couldn't open the resouce zip file. Make sure that the path is correct or that the file even exists" << std::endl;
		return 1;
	}

	/* Read the zip file */
	size_t file_size = std::filesystem::file_size(res_path);
	char* zip_data = (char*)calloc(file_size, sizeof(char));
	for (size_t i = 0; i < file_size; ++i)
		zip_data[i] = zip_file.get();
	zip_file.close();

	/* Base64 encode the zip file */
	std::string base64_zip =  cppcodec::base64_rfc4648::encode(zip_data, file_size);

	/* Add the base64 string into the headerfile */
	header_file.push_back("std::string res = \"" + base64_zip + "\";");

	/* Free any allocated zip data memory */
	free(zip_data);

	/* Write the headerfile to disk */
	std::string header_string;
	std::for_each(header_file.begin(), header_file.end(), [&](const std::string& line) { header_string += line + "\n"; });
	Birb::Filesystem::File::Write(header_path, header_string, true);

	return 0;
}
