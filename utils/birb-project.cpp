#include "STD.hpp"
#include "Filesystem.hpp"

const std::string CMAKE_TEMPLATE = R"~~(
cmake_minimum_required(VERSION 3.12)

set(PROGRAM_NAME birb_project)

project(template_project
VERSION 1.0
LANGUAGES CXX)

# Headers
include_directories(birb2d/include/)

add_subdirectory(birb2d)

add_executable(${PROGRAM_NAME} src/main.cpp)
target_link_libraries(${PROGRAM_NAME} birb2d)
target_precompile_headers(${PROGRAM_NAME} PRIVATE birb2d/include/Birb2D.hpp)

# Copy the resources into the build directory
file(COPY ./res DESTINATION ./)
)~~";

const std::string MAIN_TEMPLATE = R"~~(
#include "Birb2D.hpp"

int main(int argc, char** argv)
{
	Birb::Debug::Log("Creating the window");
	Birb::Window window("Birb2D project template", Birb::Vector2int(1280, 720), 75, false);
	Birb::TimeStep timeStep;
	timeStep.Init(&window);

	Birb::Debug::Log("Starting the game loop");
	bool ApplicationRunning = true;
	while (ApplicationRunning)
	{
		timeStep.Start();
		while (timeStep.Running())
		{
			/* Handle input stuff */
			while (window.PollEvents())
			{
				window.EventTick(window.event, &ApplicationRunning);
			}

			timeStep.Step();
		}

		window.Clear();
		/* Handle rendering */



		/* End of rendering */
		window.Display();

		timeStep.End();
	}

	return 0;
}
)~~";

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
