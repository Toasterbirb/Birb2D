#include "doctest.h"
#include "Window.hpp"
#include "Timer.hpp"

#include "../vendor/glfw/deps/linmath.h"
#include <stdlib.h>
#include <stdio.h>

/* ------------------------------------------------------------------------------------------- */
/* Most of this code is shamelessly stolen from https://www.glfw.org/docs/latest/quick.html :) */
/* ------------------------------------------------------------------------------------------- */

static const struct
{
    float x, y;
    float r, g, b;
} vertices[3] =
{
    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
    {  0.6f, -0.4f, 0.f, 1.f, 0.f },
    {   0.f,  0.6f, 0.f, 0.f, 1.f }
};

static const char* vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";

static const char* fragment_shader_text =
"#version 110\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

namespace Birb
{

	TEST_CASE("Rendering: OpenGL triangle")
	{
		Window window("OpenGL triangle", Vector2int(1280, 720), 60, false);

		GLuint vertex_buffer, vertex_shader, fragment_shader, program;
		GLint mvp_location, vpos_location, vcol_location;

		glGenBuffers(1, &vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
		glCompileShader(vertex_shader);

		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
		glCompileShader(fragment_shader);

		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		mvp_location = glGetUniformLocation(program, "MVP");
		vpos_location = glGetAttribLocation(program, "vPos");
		vcol_location = glGetAttribLocation(program, "vCol");

		glEnableVertexAttribArray(vpos_location);
		glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
							  sizeof(vertices[0]), (void*) 0);
		glEnableVertexAttribArray(vcol_location);
		glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
							  sizeof(vertices[0]), (void*) (sizeof(float) * 2));

		int width, height;
		float ratio;

		glfwGetFramebufferSize(window.glWindow, &width, &height);
		ratio = width / (float) height;

		glViewport(0, 0, width, height);

		/* Spin the triangle for 2 seconds or until the user closes the window */
		Timer timer;
		timer.Start();

		while (!glfwWindowShouldClose(window.glWindow))
		{
			if (timer.ElapsedSeconds() > 2)
				glfwSetWindowShouldClose(window.glWindow, 1);

			mat4x4 m, p, mvp;

			glClear(GL_COLOR_BUFFER_BIT);

			mat4x4_identity(m);
			mat4x4_rotate_Z(m, m, (float) glfwGetTime());
			mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
			mat4x4_mul(mvp, p, m);

			glUseProgram(program);
			glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glfwSwapBuffers(window.glWindow);
			glfwPollEvents();
		}
	}
}
