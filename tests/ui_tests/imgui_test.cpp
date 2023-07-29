#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "Birb2D.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer.h"

using namespace Birb;

void gui_start(Game& game);
void gui_input(Game& game);
void gui_update(Game& game);
void gui_render(Game& game);
void gui_post_render();
void gui_cleanup();

ImGuiIO* io;

int main(int argc, char** argv)
{
	Game::WindowOpts win_opts;
	Game game(win_opts, gui_start, gui_input, gui_update, gui_render);

	game.Start();
	return 0;
}

void gui_start(Game& game)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO(); (void)io;
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	//ImGui_ImplSDL2_InitForSDLRenderer(game.window->win, game.window->renderer);
	//ImGui_ImplSDLRenderer_Init(game.window->renderer);
}

void gui_input(Game& game)
{
	ImGui_ImplSDL2_ProcessEvent(game.event);
}

bool my_tool_active = true;
float my_color[4];

void gui_update(Game& game)
{
	ImGui_ImplSDLRenderer_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	{
		// Create a window called "My First Tool", with a menu bar.
		ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
				if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
				if (ImGui::MenuItem("Close", "Ctrl+W"))  { my_tool_active = false; }
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		// Edit a color stored as 4 floats
		ImGui::ColorEdit4("Color", my_color);

		// Generate samples and plot them
		float samples[100];
		for (int n = 0; n < 100; n++)
			samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
		ImGui::PlotLines("Samples", samples, 100);

		// Display contents in a scrolling region
		ImGui::TextColored(ImVec4(1,1,0,1), "Important Stuff");
		ImGui::BeginChild("Scrolling");
		for (int n = 0; n < 50; n++)
			ImGui::Text("%04d: Some text", n);
		ImGui::EndChild();
		ImGui::End();
	}
}

void gui_render(Game& game)
{
	ImGui::Render();
	SDL_RenderSetScale(game.window->renderer, io->DisplayFramebufferScale.x, io->DisplayFramebufferScale.y);
	ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}

void gui_post_render()
{

}

void gui_cleanup()
{
	ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}
