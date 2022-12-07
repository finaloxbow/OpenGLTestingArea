#include "Renderer.h"

#include "Utils.h"

Renderer::Renderer(unsigned int framebuffer_width, unsigned int framebuffer_height, unsigned int channels, GLFWwindow* window)
	: m_framebuffer_width(framebuffer_width), m_framebuffer_height(framebuffer_height),  m_channels(channels), m_window(window) {

	//opengl init
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw "GLAD init failed.";

	//framebuffer creation and setup
	unsigned int buffer_size = m_framebuffer_height * m_framebuffer_width * m_channels;
	m_framebuffer = new GLubyte[buffer_size];
	framebuffer_setup();
}

void Renderer::updatePixel(unsigned int x, unsigned int y, unsigned int rgbaVal)
{
	if (x >= 0 && x < m_framebuffer_height && y >= 0 && y < m_framebuffer_width) {

		GLubyte red = (rgbaVal & 0xff000000) >> (6 * 4);
		GLubyte green = (rgbaVal & 0x00ff0000) >> (4 * 4);
		GLubyte blue = (rgbaVal & 0x0000ff00) >> (4 * 2);
		GLubyte alpha = (rgbaVal & 0x000000ff);

		m_framebuffer[x * m_framebuffer_width * 4 + y * 4 + 0] = red;
		m_framebuffer[x * m_framebuffer_width * 4 + y * 4 + 1] = green;
		m_framebuffer[x * m_framebuffer_width * 4 + y * 4 + 2] = blue;
		m_framebuffer[x * m_framebuffer_width * 4 + y * 4 + 3] = alpha;
	}
}

void Renderer::updatePixel(unsigned int x, unsigned int y, glm::vec4& rgba, int samples_per_pixel)
{
	auto red = rgba.x;
	auto green = rgba.y;
	auto blue = rgba.z;
	auto alpha = rgba.t;

	auto scale = 1.0f / samples_per_pixel;
	red = sqrt(scale * red);
	green = sqrt(scale * green);
	blue = sqrt(scale * blue);

	m_framebuffer[x * m_framebuffer_width * 4 + y * 4 + 0] = static_cast<int>(256 * clamp(red, 0.0f, 0.999f));
	m_framebuffer[x * m_framebuffer_width * 4 + y * 4 + 1] = static_cast<int>(256 * clamp(green, 0.0f, 0.999f));
	m_framebuffer[x * m_framebuffer_width * 4 + y * 4 + 2] = static_cast<int>(256 * clamp(blue, 0.0f, 0.999f));
	m_framebuffer[x * m_framebuffer_width * 4 + y * 4 + 3] = static_cast<int>(256 * clamp(alpha, 0.0f, 0.999f));
}

void Renderer::swap_buffers(unsigned int drawBuffer)
{
	//update texture
	glTexSubImage2D(
		GL_TEXTURE_2D,
		0,
		0,
		0,
		m_framebuffer_width,
		m_framebuffer_height,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		m_framebuffer
	);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_framebufferID);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, drawBuffer);
	glBlitFramebuffer(
		0, 0, m_framebuffer_width, m_framebuffer_height,
		0, 0, m_framebuffer_width, m_framebuffer_height,
		GL_COLOR_BUFFER_BIT, GL_NEAREST);

	glfwSwapBuffers(m_window);
}

unsigned int Renderer::getBufferWidth()
{
	return m_framebuffer_width;
}

unsigned int Renderer::getBufferHeight()
{
	return m_framebuffer_height;
}

void Renderer::framebuffer_setup()
{
	//data alignment stuff
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

	//texture creation
	glGenTextures(1, &m_texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		m_framebuffer_width,
		m_framebuffer_height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		m_framebuffer
	);

	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//generates texture mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	//creates framebuffer and attaches previous texture to it
	glGenFramebuffers(1, &m_framebufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
	glFramebufferTexture(
		GL_FRAMEBUFFER,
		GL_COLOR_ATTACHMENT0,
		m_texture,
		0
	);
}
