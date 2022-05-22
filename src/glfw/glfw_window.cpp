#ifdef LIB_GLFW
#include "Window.hpp"
#include "Logger.hpp"

namespace Birb
{
	void Window::bGLFW_InitWindow(const bool& resizable)
	{
		/* ------------------------- */
		/* GLFW Window implementation */
		/* ------------------------- */

		/* Initialize GLFW stuff */
		glfwSetErrorCallback(Debug::error_callback);

		if (!glfwInit())
		{
			Debug::Log("Failed to initialize GLFW", Debug::error);
			exit(1);
		}

		/* Create the window */
		if (resizable)
			glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		else
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		glWindow = glfwCreateWindow(dimensions.x, dimensions.y, win_title.c_str(), NULL, NULL);
		if (!glWindow)
		{
			Debug::Log("Something went wrong when creating GLFW window", Debug::error);
			glfwTerminate();
			exit(1);
		}


		/* Make the window current context */
		glfwMakeContextCurrent(glWindow);

		/* Load up glad */
		gladLoadGL(glfwGetProcAddress);

		/* Set buffer swapping interval to 1 */
		glfwSwapInterval(1);

		/* Get the framebuffer size and set it to the viewport */
		glfwGetFramebufferSize(glWindow, &frameBufferWidth, &frameBufferHeight);
		glViewport(0, 0, frameBufferWidth, frameBufferHeight);

		/* Clear the window so that it isn't near invisible */
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(glWindow);
	}
}
#endif
