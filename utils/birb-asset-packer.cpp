#include "Birb2D.hpp"

void PrintHelp()
{
	std::cout << "## Birb Asset Packer ##\n" <<
"This tool is used for packing Birb2D assets into an easy to read binary blob.\nThis should *in theory* speed up the game loading times and stuff by reducing unnecessary disk I/O\n" << std::endl;

	std::cout << "Options:\n\
  -h			Prints this help page\n\
  -p [res path]		Path to a resource directory to pack\n\
  -o [output] 		File path for the resulting binary file\n\
  -i [asset file] 	List the contents of an asset file" << std::endl;
}

void PrintInvalidArgument()
{
	std::cout << "Invalid arguments. Check the output of \"-h\" for help" << std::endl;
}

enum Mode
{
	PACKING, INSPECTING, NONE
};

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		PrintHelp();
		return 0;
	}

	Mode execution_mode = Mode::NONE;

	/* Make sure that the first argument is an option */
	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] == '-')
		{
			switch (execution_mode)
			{
				case (NONE):
				{
					switch (argv[i][1])
					{
						case('h'):
							PrintHelp();
							break;

						case('p'):
							execution_mode = Mode::PACKING;
							break;

						case('o'):
							break;

						case('i'):
							execution_mode = Mode::INSPECTING;
							break;

						default:
							PrintInvalidArgument();
							return 1;
					}

					break;
				}

				case (PACKING):
				{
					break;
				}

				case (INSPECTING):
				{
					break;
				}
			}
		}
		else
		{
			PrintInvalidArgument();
			return 1;
		}
	}
}
