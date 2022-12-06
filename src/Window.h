#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
private:
	unsigned int m_width, m_height;
	GLFWwindow* m_windowPtr;

	void processInput();
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:

	Window(unsigned int width, unsigned int height, const char* windowName);
	~Window();

	GLFWwindow* getWindowPtr();
	unsigned int getWidth();
	unsigned int getHeight();

	void frameUpdate();


};