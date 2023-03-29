#pragma once

#include <vector>
#include <glad/glad.h>

struct vbe {
	//number of elements
	unsigned int count;
	//type of elements
	unsigned int type;
	//normalized to (-1, 1)
	bool normalized;

	static unsigned int get_size_of_type(unsigned int type) {
		switch (type) {
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}
	
		return 0;
	}
};

class vbo_layout {
private:
	std::vector<vbe> m_elements;
	unsigned int m_stride;

	void push_helper(unsigned int count, unsigned int type) {
		struct vbe elem = { count, type, false};
		m_elements.push_back(elem);
		m_stride += count * vbe::get_size_of_type(type);
	}

public:
	vbo_layout() : m_stride(0) {}

	template<typename T>
	void push(unsigned int count){}

	template<>
	void push<float>(unsigned int count) {
		push_helper(count, GL_FLOAT);
	}
	template <>
	void push<unsigned int>(unsigned int count) {
		push_helper(count, GL_UNSIGNED_INT);
	}
	template <>
	void push<GLubyte>(unsigned int count) {
		push_helper(count, GL_UNSIGNED_BYTE);
	}

	std::vector<vbe> get_elements() const { return m_elements; }
	inline unsigned int get_stride() const { return m_stride; }
};