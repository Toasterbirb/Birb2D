#include "STD.hpp"
#include "Filesystem.hpp"

const std::string CMAKE_TEMPLATE = 
	R"~~(cmake_minimum_required(VERSION 3.12)

set(PROGRAM_NAME birb_project)

project(template_project
VERSION 1.0
LANGUAGES CXX)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif(CCACHE_FOUND)

# Headers
include_directories(include)
include_directories(birb2d/include/)

add_subdirectory(birb2d)
include_directories(birb2d/vendor/SDL/include)

add_executable(${PROGRAM_NAME} src/main.cpp)
target_link_libraries(${PROGRAM_NAME} birb2d)
target_precompile_headers(${PROGRAM_NAME} PRIVATE birb2d/include/Birb2D.hpp)

# Copy the resources into the build directory
file(COPY ./res DESTINATION ./)
file(COPY ./birb2d/birb2d_res DESTINATION ./res/))~~";

const std::string MAIN_TEMPLATE = 
R"~~(#include "Birb2D.hpp"

using namespace Birb;

/* Function declarations */
static void start(Game& game);
static void input(Game& game);
static void update(Game& game);
static void render(Game& game);
static void post_render();
static void cleanup();

int main(void)
{
	Game::WindowOpts window_options;
	window_options.title 				= "Game";
	window_options.window_dimensions 	= { 1280, 720 };
	window_options.refresh_rate 		= 75;
	window_options.resizable 			= false;

	Game game_loop(window_options, start, input, update, render);

	/* Optional extra functions */
	game_loop.post_render = post_render;
	game_loop.cleanup = cleanup;

	/* Start the game loop */
	game_loop.Start();

	return 0;
}

/* start() is called before the game loop starts.
 * Useful for doing stuff that will only run once before
 * the game starts */
void start(Game& game)
{

}

/* input() is called at the beginning of the frame
 * before update(). Behind the curtains it does input
 * polling etc. and then passes the SDL_Event into
 * this function */
void input(Game& game)
{

}

/* update() is called after input has been handled and
 * before the frame gets rendered. Its useful for any game
 * logic that needs to be updated before rendering */
void update(Game& game)
{

}

/* render() is called after update() has been finished.
 * Before it gets called, the window will be cleared and
 * after the function has finished running, the rendered frame
 * will be presented */
void render(Game& game)
{

}

/* post_render() will be called after rendering has finished
 * and the timestep stalling has started. On non-windows systems
 * this function call will be done on a separate thread, so you
 * could use it to do some extra preparations for the next frame
 * while the main thread is sitting around doing nothing
 * and waiting to maintain the correct frame rate */
void post_render()
{

}

/* cleanup() gets called after the game loop has finished running
 * and the application is getting closed. This is useful for doing any
 * cleanup that is necessary, like freeing heap allocations etc. */
void cleanup()
{

})~~";

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


int main(void)
{
	Project project;

	std::cout << "\033[32mWelcome to the Birb2D project wizard!\033[0m\n";

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
			std::cout << "\033[31mBirb2D source wasn't provided. You need to clone it manually!\033[0m\n";
		}

		std::cout << "Creating some project files...\n";
		Birb::Filesystem::File::Write(project.project_path + "/CMakeLists.txt", CMAKE_TEMPLATE);
		Birb::Filesystem::File::Write(project.project_path + "/src/main.cpp", MAIN_TEMPLATE);

		std::cout << "\033[32mProject created!\033[0m\n";
	}

	return 0;
}
