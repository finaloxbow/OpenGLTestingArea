#include "vbo.h"
#include <glad/glad.h>

vbo::vbo(const void* data, unsigned int size)
{
	glGenBuffers(1, &m_rendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

vbo::~vbo()
{
	glDeleteBuffers(1, &m_rendererID);
}

void vbo::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
}

void vbo::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
