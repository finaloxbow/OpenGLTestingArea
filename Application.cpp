#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


unsigned int SCR_WIDTH = 1280;
unsigned int SCR_HEIGHT = 720;

const char* vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"out vec3 ourColor;\n"
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;\n"
"   TexCoord = aTexCoord;\n"
"}\n";

const char* fragmentShaderSource = 
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D ourTexture;\n"
"void main()\n"
"{\n"
"   FragColor = texture(ourTexture, TexCoord);\n"
"}\n";

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
			unsigned int color = 0x8a16c4ff;
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

	//create shaders and shader program
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//vertices for main quad
	float vertices[] = {
		-1.0f,  1.0f, 0.0f,	1.0f, 1.0f, 0.0f, 0.0f, 1.0f,//top left
		 1.0f,  1.0f, 0.0f,	1.0f, 0.0f, 0.0f, 1.0f, 1.0f,//top right
		-1.0f, -1.0f, 0.0f,	0.0f, 0.0f, 1.0f, 0.0f, 0.0f,//bottom left
		 1.0f, -1.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f, 0.0f//bottom right
	};

	unsigned int indices[] = {
		0, 3, 2,
		0, 1, 3
	};

	//creating objects for quad rendering
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//texture creation
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

	glGenerateMipmap(GL_TEXTURE_2D);

	//main application loop
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

		glBindTexture(GL_TEXTURE_2D, texture);

		//drawing the quad to fill the screen
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		processInput(window);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}