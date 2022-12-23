#pragma once
#include "Renderwindow.hpp"
#include "Entity.hpp"
#include "Scene.hpp"

namespace Birb
{
	/// Creates simple splash screens with a customizable scene
	class Splash
	{
	public:
		Splash(Window& window, bool isCustom = false); ///< Creates the default Birb2D splash screen
		~Splash();

		Scene scene;
		float duration; ///< Splash screen duration in seconds
		bool isCustom; 	///< Change this to true if you want to use a custom
						/// splash screen.

		void Run();

	private:
		Window& window;
		Font manaspace;
		Font manaspace_small;

		Entity background_plane;
		Entity birb2d_logo;
		Entity birb2d_text;

		Entity loading_text;

	};
}
