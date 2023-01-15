#pragma once
#include "AssetManager.hpp"
#include "Entities/Image.hpp"
#include "Entities/Text.hpp"
#include "Font.hpp"
#include "Renderwindow.hpp"
#include "Scene.hpp"

namespace Birb
{
	/// Creates simple splash screens with a customizable scene
	class Splash
	{
	public:
		Splash(Window& window, bool isCustom = false); ///< Creates the default Birb2D splash screen

		Scene scene;
		float duration; ///< Splash screen duration in seconds
		bool isCustom; 	///< Change this to true if you want to use a custom
						/// splash screen.

		/// Text used for the loading screen frame
		std::string loading_text;

		void Run();

	private:
		AssetManager asset_manager;

		Window& window;
		Font manaspace;
		Font manaspace_small;

		Rect background_plane;
		Entity::Image birb2d_logo;
		Entity::Text birb2d_text;

		Entity::Text loading_text_entity;

		Scene loading_scene;
	};
}
