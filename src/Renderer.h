#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Renderer {
public:
	//TODO: add destructor to cleanup texture, framebuffer, etc.
	Renderer(unsigned int framebuffer_width, 
		unsigned int framebuffer_height, 
		unsigned int channels,
		GLFWwindow* window);

	void updatePixel(unsigned int x, unsigned int y, unsigned int rgbaVal);
	void updatePixel(unsigned int x, unsigned int y, glm::vec4& rgba, int samples_per_pixel);
	void swap_buffers(unsigned int drawBuffer);
	unsigned int getBufferWidth();
	unsigned int getBufferHeight();
private:
	 unsigned int m_framebuffer_width, m_framebuffer_height, m_channels;
	 GLubyte* m_framebuffer;
	 GLFWwindow* m_window;
	 unsigned int m_framebufferID;
	 unsigned int m_texture;

	 void framebuffer_setup();

};