#pragma once

#include <glad/glad.h>

#include <optional>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class shader {
private:
	unsigned int m_ID;

	std::optional<std::string> load_shader_from_file(const char* filepath);

	void check_compile_errors(unsigned int shader, std::string type);

public:
	shader(const char* vertex_path, const char* fragment_path);

	void use();
};