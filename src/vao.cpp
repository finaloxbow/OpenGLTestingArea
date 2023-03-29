#include "vao.h"

vao::vao()
{
	glGenVertexArrays(1, &m_rendererID);
	glBindVertexArray(m_rendererID);
}

vao::~vao()
{
	glDeleteVertexArrays(1, &m_rendererID);
}

void vao::add_buffer(vbo& vb, vbo_layout& layout)
{
	bind();
	vb.bind();
	unsigned long long offset = 0;
	const auto& elements = layout.get_elements();
	for (int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.get_stride(), (void*)offset);
		offset += (unsigned long long)element.count * vbe::get_size_of_type(element.type);
	}
}

void vao::bind() const
{
	glBindVertexArray(m_rendererID);
}

void vao::unbind() const
{
	glBindVertexArray(0);
}
