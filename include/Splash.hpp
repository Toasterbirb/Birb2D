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
		Splash(Window& window); ///< Creates the default Birb2D splash screen

		Scene scene;
		float duration; ///< Splash screen duration in seconds
		bool isCustom; 	///< Change this to true if you want to use a custom
						/// splash screen

		bool insertLoadingScreenFrame;
		void Run();

	private:
		Window& window;
		Entity background_plane;
		Entity birb2d_logo;
		Entity birb2d_text;
		Font manaspace;
	};
}
