#include "texture.h"

texture::texture(unsigned int texture_slot)
	: m_slot(texture_slot)
{
	glGenTextures(1, &m_ID);
	glActiveTexture(texture_slot);
	glBindTexture(GL_TEXTURE_2D, m_ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void texture::load_img_into_texture(const char* filepath, unsigned int texture_format, unsigned int img_format)
{
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);
	if (!data)
		throw "Failed to load image into texture.";

	glTexImage2D(GL_TEXTURE_2D, 0, texture_format, width, height, 0, img_format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

void texture::use()
{
	glActiveTexture(m_slot);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}
