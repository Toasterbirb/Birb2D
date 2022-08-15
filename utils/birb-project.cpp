#include "STD.hpp"
#include "Filesystem.hpp"

#define CMAKE_TEMPLATE "\
cmake_minimum_required(VERSION 3.12)\n\
project(template_project\n\
VERSION 1.0\n\
LANGUAGES CXX)\n\
\n\
# Headers \n\
include_directories(birb2d/include/) \n\
include_directories(birb2d/vendor/SDL2_gfx/)\n\
\n\
add_subdirectory(birb2d)\n\
\n\
add_executable(birb_project src/main.cpp)\n\
target_link_libraries(birb_project birb2d)\n\
\n\
# Copy the resources into the build directory\n\
file(COPY ./res DESTINATION ./)\n"

#define MAIN_TEMPLATE "\
#include \"Renderwindow.hpp\"\n\
#include \"Timestep.hpp\"\n\
\n\
int main(int argc, char** argv)\n\
{\n\
	Birb::Debug::Log(\"Creating the window\");\n\
	Birb::Window window(\"Birb2D project template\", Birb::Vector2int(1280, 720), 75, false);\n\
	Birb::TimeStep timeStep;\n\
	timeStep.Init(&window);\n\
\n\
	Birb::Debug::Log(\"Starting the game loop\");\n\
	bool ApplicationRunning = true;\n\
	while (ApplicationRunning)\n\
	{\n\
		timeStep.Start();\n\
		while (timeStep.Running())\n\
		{\n\
			/* Handle input stuff */\n\
			while (window.PollEvents())\n\
			{\n\
				window.EventTick(window.event, &ApplicationRunning);\n\
			}\n\
\n\
			timeStep.Step();\n\
		}\n\
\n\
		window.Clear();\n\
		/* Handle rendering */\n\
\n\
\n\
\n\
		/* End of rendering */\n\
		window.Display();\n\
\n\
		timeStep.End();\n\
	}\n\
\n\
	return 0;\n\
}\n\
"

struct Project
{
	std::string project_path;
	std::string birb_path;
};

bool YesNoPrompt(const std::string message)
{
    std::cout << message << " (y/n): ";
    std::string answer = "";
    std::cin >> answer;
    if (answer != "yes" && answer != "Yes" && answer != "Y" && answer != "y")
        return false;
    else
        return true;
}

std::string ExpandHomePath(const std::string& filepath)
{
	if (filepath[0] != '~')
		return filepath;

	std::string home_dir = (std::string)getenv("HOME");

	return home_dir + filepath.substr(1, filepath.length() - 1);
}


int main(int argc, char** argv)
{
	Project project;

	std::cout << "\e[32mWelcome to the Birb2D project wizard!\e[0m\n";

	std::cout << "Project path: ";
	std::cin >> project.project_path;

	std::cout << "Path to the root of Birb2D source code (optional, type 'none' to skip): ";
	std::cin >> project.birb_path;

	/* Handle the ~ chars */
	project.project_path = ExpandHomePath(project.project_path);
	project.birb_path = ExpandHomePath(project.birb_path);

	/* Confirm the information */
	std::cout << "--------------------------" << std::endl;

	if (std::filesystem::exists(project.project_path))
		std::cout << "Path: " << project.project_path << " [overwrite an existing directory]" << std::endl;
	else
		std::cout << "Path: " << project.project_path << std::endl;

	std::cout << "Path to Birb2D: " << project.birb_path << std::endl;


	if (YesNoPrompt("Is this correct?"))
	{
		std::cout << "Creating directories...\n";
		std::filesystem::create_directories(project.project_path);

		if (!std::filesystem::exists(project.project_path) || !std::filesystem::is_directory(project.project_path))
		{
			std::cerr << "Couldn't create the project directory. Quitting\n";
			return 1;
		}

		std::filesystem::create_directories(project.project_path + "/src");
		std::filesystem::create_directories(project.project_path + "/include");
		std::filesystem::create_directories(project.project_path + "/res");

		if (project.birb_path != "none")
		{
			std::cout << "Symlinking Birb2D...\n";
			std::filesystem::create_symlink(project.birb_path, project.project_path + "/birb2d");
		}
		else
		{
			std::cout << "\e[31mBirb2D source wasn't provided. You need to clone it manually!\e[0m\n";
		}

		std::cout << "Creating some project files...\n";
		Birb::Filesystem::File::Write(project.project_path + "/CMakeLists.txt", CMAKE_TEMPLATE);
		Birb::Filesystem::File::Write(project.project_path + "/src/main.cpp", MAIN_TEMPLATE);

		std::cout << "\e[32mProject created!\e[0m\n";
	}

	return 0;
}
