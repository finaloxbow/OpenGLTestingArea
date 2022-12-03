#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


unsigned int SCR_WIDTH = 1280;
unsigned int SCR_HEIGHT = 720;


void processInput(GLFWwindow* window)
{

	//close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

}

int main() {

	if (!glfwInit()) {
		std::cout << "GLFW INIT FAILED.\n";
		return EXIT_FAILURE;
	}

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Ray Tracer", NULL, NULL);
	if (window == NULL) {
		std::cout << "Window creation failed.\n";
		return EXIT_FAILURE;
	}

	glfwSetWindowPos(window, SCR_WIDTH / 2, SCR_HEIGHT / 2);
	glfwSwapInterval(0);

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//creating the buffer
	//TODO: fix to not hardcode values
	auto data = new GLubyte[720][1280][4];
	for (int i = 0; i < SCR_HEIGHT; i++) {
		for (int j = 0; j < SCR_WIDTH; j++) {
			unsigned int color = 0x8a1600ff;
			GLubyte red = (color & 0xff000000) >> (6 * 4);
			GLubyte green = (color & 0x00ff0000) >> (4 * 4);
			GLubyte blue = (color & 0x0000ff00) >> (4 * 2);
			GLubyte alpha = (color & 0x000000ff);

			data[i][j][0] = red;
			data[i][j][1] = green;
			data[i][j][2] = blue;
			data[i][j][3] = alpha;
		}
	}

	//data alignment stuff
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//texture creation stuff
	unsigned int texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	//sets the data of the texture
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		SCR_WIDTH,
		SCR_HEIGHT,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		data
	);

	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//generates texture mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	//creates framebuffer and attaches previous texture to it
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glFramebufferTexture(
		GL_FRAMEBUFFER, 
		GL_COLOR_ATTACHMENT0,
		texture, 
		0);

	//main application loop
	while (!glfwWindowShouldClose(window)) {

		//reads data from created framebuffer to the default one, rendering the pixel data on the screen
		glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBlitFramebuffer(
		0, 0, SCR_WIDTH, SCR_HEIGHT,
		0, 0, SCR_WIDTH, SCR_HEIGHT,
		GL_COLOR_BUFFER_BIT, GL_NEAREST);


		//update the image on the screen
		glTexSubImage2D(
			GL_TEXTURE_2D,
			0,
			0,
			0,
			SCR_WIDTH,
			SCR_HEIGHT,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			data
		);

		processInput(window);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}