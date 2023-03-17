#include "shader.h"

std::optional<std::string> shader::load_shader_from_file(const char* filepath) {
	std::ifstream f(filepath);
	if (f) {
		std::ostringstream ss;
		ss << f.rdbuf();
		return ss.str();
	}

	return {};
}

void shader::check_compile_errors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];

	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "Shader type: " << type << "\n" << infoLog << "\n -----------------\n";
			throw "Shader creation failed.";
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "Program type: " << type << "\n" << infoLog << "\n -----------------\n";
			throw "Program creation failed.";
		}
	}

}

shader::shader(const char* vertex_path, const char* fragment_path)
{
	//reading shaders from files
	auto vs = load_shader_from_file(vertex_path);
	if (!vs.has_value())
		throw "Reading vertex shader failed.";

	auto fs = load_shader_from_file(fragment_path);
	if (!fs.has_value())
		throw "Reading fragment shader failed.";

	//convert to char* strings
	const char* vertexShaderSource = vs.value().c_str();
	const char* fragmentShaderSource = fs.value().c_str();


	//shader creation and error checking
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	check_compile_errors(vertexShader, "VERTEX");

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	check_compile_errors(fragmentShader, "FRAGMENT");

	//shader program creation
	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexShader);
	glAttachShader(m_ID, fragmentShader);
	glLinkProgram(m_ID);
	check_compile_errors(m_ID, "PROGRAM");

	//shader cleanup
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void shader::use()
{
	glUseProgram(m_ID);
}
