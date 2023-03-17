#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>

class texture {
private:
	unsigned int m_ID;
	unsigned int m_slot;

public:

	texture(unsigned int texture_slot);
	
	void load_img_into_texture(const char* filepath, unsigned int texture_format, unsigned int img_format);

	void use();
};