#pragma once

#include <glad/glad.h>
#include <string>

enum class ShaderType {
	NONE = -1,
	VERTEX = 0,
	FRAGMENT = 1
};

class Shader {
public:
	Shader();
	~Shader();

	void create(const std::string& shaderFilePath);
	void bind();
	void unbind();

private:
	unsigned int m_RendererID;
	std::string m_filePath;
	
	static unsigned int compileShader(unsigned int type, const std::string& source);
	static std::pair<std::string, std::string> parseShader(const std::string& filePath);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
	
};