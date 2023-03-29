#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "camera.h"
#include "texture.h"
#include "vao.h"
#include "vbo.h"
#include "vbo_layout.h"

#include <stb/stb_image.h>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <optional>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

//MAKE CAMERA HERE!!
float last_x = SCR_WIDTH / 2.0f;
float last_y = SCR_HEIGHT / 2.0f;
camera cam;
bool first_mouse = true;
float delta_time = 0.0f;
float last_frame = 0.0f;

//lighting
glm::vec3 light_pos(1.0f, 1.0f, 2.0f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam.process_keyboard(camera::CAMERA_MOVEMENT::FORWARD, delta_time);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam.process_keyboard(camera::CAMERA_MOVEMENT::BACKWARD, delta_time);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam.process_keyboard(camera::CAMERA_MOVEMENT::LEFT, delta_time);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam.process_keyboard(camera::CAMERA_MOVEMENT::RIGHT, delta_time);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (first_mouse) {
		last_x = xposIn;
		last_y = yposIn;
		first_mouse = false;
	}

	float xoffset = xpos - last_x;
	float yoffset = last_y - ypos;

	last_x = xpos;
	last_y = ypos;

	cam.process_mouse_movement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	cam.process_mouse_scroll(static_cast<float>(yoffset));
}

int main() {
	
	//set stb to read inverted image for OpenGL compat
	stbi_set_flip_vertically_on_load(true);

	//initialize glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (!window) {
		glfwTerminate();
		throw "Window creation failed.";
	}

	//make opengl context and set callback functions
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw "OpenGL init failed.";

	//enable depth checking
	glEnable(GL_DEPTH_TEST);

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	//set shader program
	shader regular_cube("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");
	shader light_cube("res/shaders/light_vertex.glsl", "res/shaders/light_fragment.glsl");
	//create VBOs, VAOs, and layout

	vbo cube_data(vertices, sizeof(vertices));

	vao cube_vao;
	vbo_layout cube_vao_layout;
	cube_vao_layout.push<float>(3);
	cube_vao_layout.push<float>(3);
	cube_vao.add_buffer(cube_data, cube_vao_layout);

	vao light_vao;
	light_vao.add_buffer(cube_data, cube_vao_layout);

	while (!glfwWindowShouldClose(window)) {
		//do program stuff
		float current_frame = static_cast<float>(glfwGetTime());
		delta_time = current_frame - last_frame;
		last_frame = current_frame;

		processInput(window);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		regular_cube.use();
		regular_cube.set_fvec3("object_color", glm::vec3(1.0f, 0.5f, 0.31f));
		regular_cube.set_fvec3("light_color", glm::vec3(1.0f, 1.0f, 1.0f));
		regular_cube.set_fvec3("light_pos", light_pos);
		regular_cube.set_fvec3("view_pos", cam.m_position);

		glm::mat4 projection = glm::perspective(
			glm::radians(cam.m_zoom),
			(float)SCR_WIDTH / (float)SCR_HEIGHT,
			0.1f,
			100.0f
		);
		glm::mat4 view = cam.get_view_matrix();
		regular_cube.set_fmat4("projection", projection);
		regular_cube.set_fmat4("view", view);
		
		glm::mat4 model = glm::mat4(1.0f);
		regular_cube.set_fmat4("model", model);

		cube_vao.bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		light_cube.use();
		light_cube.set_fmat4("projection", projection);
		light_cube.set_fmat4("view", view);
		model = glm::mat4(1.0f);
		light_pos.x = 2.0f*sin(glfwGetTime());
		light_pos.z = 2.0f*cos(glfwGetTime());
		model = glm::translate(model, light_pos);
		model = glm::scale(model, glm::vec3(0.2f));
		light_cube.set_fmat4("model", model);

		light_vao.bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}