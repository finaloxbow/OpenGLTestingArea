#pragma once

#include <glad/glad.h>

#include <optional>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class shader {
private:
	unsigned int m_ID;

	std::optional<std::string> load_shader_from_file(const char* filepath);

	void check_compile_errors(unsigned int shader, std::string type);

public:
	shader(const char* vertex_path, const char* fragment_path);

	void use();

	//setting uniforms
	void set_float(const std::string& name, float value) const;
	void set_bool(const std::string& name, bool value) const;
	void set_int(const std::string& name, int value) const;
	void set_fvec3(const std::string& name, glm::vec3 value) const;
	void set_fmat4(const std::string& name, glm::mat4 value) const;
};