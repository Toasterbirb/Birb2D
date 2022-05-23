#ifdef LIB_GLFW
#include "Window.hpp"
#include "Logger.hpp"

namespace Birb
{
	Window::Window() {}

	Window::Window(const std::string& p_title, const Vector2int& p_window_dimensions, const int& p_refresh_rate, const bool& resizable)
	:win_title(p_title), refresh_rate(p_refresh_rate), dimensions(p_window_dimensions), original_window_dimensions(p_window_dimensions), resizable(resizable)
	{
		/* ------------------------- */
		/* GLFW Window implementation */
		/* ------------------------- */

		Debug::Log("Creating window '" + win_title + "'...");

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
		glfwSetWindowSizeCallback(glWindow, window_size_callback);


		/* Make the window current context */
		glfwMakeContextCurrent(glWindow);

		/* Load up glad */
		gladLoadGL(glfwGetProcAddress);

		/* Set buffer swapping interval to 1 */
		glfwSwapInterval(1);

		/* Get the framebuffer size and set it to the viewport */
		int width, height;
		glfwGetFramebufferSize(glWindow, &width, &height);
		glViewport(0, 0, width, height);

		/* Clear the window so that it isn't near invisible */
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(glWindow);

		Global::RenderVars::RefreshRate = refresh_rate;

		Debug::Log("Window '" + win_title + "' created successfully!");
	}

	void Window::Cleanup()
	{
		Debug::Log("Starting window cleanup for '" + win_title + "'...");

		glfwDestroyWindow(glWindow);
		glfwTerminate();

		Debug::Log("Window '" + win_title + "' destroyed!");
	}

	void Window::Clear()
	{
		/* Clear the window renderer. Call before rendering stuff */
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::Display()
	{
		glfwSwapBuffers(glWindow);
	}

	Vector2int Window::CursorPosition() const
	{
		Vector2int pos;
		Debug::Log("CursorPosition() not implemented", Debug::fixme);
		return pos;
	}

	void Window::SetWindowSize(const Vector2int& dimensions)
	{
		glfwSetWindowSize(glWindow, dimensions.x, dimensions.y);
		this->dimensions = dimensions;
	}

	void Window::EventTick(bool* GameRunning)
	{
		/* Check if the window should close */
		if (*glfwWindowShouldClose)
			*GameRunning = false;
	}

	bool Window::PollEvents()
	{
		glfwPollEvents();
		return false;
	}

	/* GLFW Specific functions */
	void Window::window_size_callback(GLFWwindow* window, int width, int height)
	{
		/* Update the viewport size if the window has been resized */
		int frameBufferWidth, frameBufferHeight;
		glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
		glViewport(0, 0, frameBufferWidth, frameBufferHeight);
	}

	Vector2int Window::FrameBufferDimensions()
	{
		Vector2int frameBufferDimensions;
		glfwGetFramebufferSize(glWindow, &frameBufferDimensions.x, &frameBufferDimensions.y);
		return frameBufferDimensions;
	}

}
#endif
