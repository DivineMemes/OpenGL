#pragma once
#include "context.h"
#include <cstdio>

#include "glew/glew.h"
#include "glfw/glfw3.h"
bool context::init(int w, int h, const char * title)
{
	//init glfw
	glfwInit();

	window = glfwCreateWindow(w, h, title, nullptr, nullptr);

	glfwMakeContextCurrent(window);

	//init glew
	glewInit();
	


	//print out diagnostics
	printf("OpenGL Version: %s\n", (const char *)glGetString(GL_VERSION));
	printf("Renderer: %s\n", (const char *)glGetString(GL_RENDERER));
	printf("Vendor: %s\n", (const char *)glGetString(GL_VENDOR));
	printf("GLSL: %s\n", (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION));


	glClearColor(0.25f, 0.25f, 0.25f, 1);
	return true;
}


void context::tick()
{
	glfwPollEvents();
	glfwSwapBuffers(window);
}

void context::term()
{
	glfwDestroyWindow(window);
	glfwTerminate();

}

void context::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool context::shouldClose() const
{
	return glfwWindowShouldClose(window);
}
