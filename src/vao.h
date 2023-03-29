#pragma once

#include "vbo.h"
#include "vbo_layout.h"

class vao {
private:
	unsigned int m_rendererID;

public:
	vao();
	~vao();

	void add_buffer(vbo& vb, vbo_layout& layout);

	void bind() const;
	void unbind() const;
};