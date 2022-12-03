#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>

Shader::Shader() 
	: m_RendererID(0) {}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::create(const std::string& shaderFilePath)
{
	auto source = parseShader(shaderFilePath);

	std::cout << "----------VERTEX SHADER-----------\n";
	std::cout << source.first << "\n";
	std::cout << "----------FRAGMENT SHADER---------\n";
	std::cout << source.second << "\n";

	m_RendererID = createShader(source.first, source.second);
}

void Shader::bind()
{
	glUseProgram(m_RendererID);
}

void Shader::unbind()
{
	glUseProgram(0);
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
	unsigned int idShader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(idShader, 1, &src, nullptr);
	glCompileShader(idShader);

	return idShader;
}

std::pair<std::string, std::string> Shader::parseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			if (type != ShaderType::NONE)
				ss[(int)type] << line << "\n";
		}
	}

	return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
