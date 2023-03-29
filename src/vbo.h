#pragma once

class vbo {
private:
	unsigned int m_rendererID;

public:
	vbo(const void* data, unsigned int size);
	~vbo();

	void bind();
	void unbind();
};