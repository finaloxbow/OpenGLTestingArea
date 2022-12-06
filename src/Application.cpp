#include "Application.h"

#include <glm/glm.hpp>
#include "Ray.h"

Window* Application::window;
Renderer* Application::renderer;

void Application::setup()
{
	window = new Window(scrWidth, scrHeight, "Ray Tracing");
	renderer = new Renderer(scrWidth, scrHeight, numChannels, window->getWindowPtr());

	auto viewport_height = 2.0;
	auto viewport_width = (16.0 / 9.0) * viewport_height;
	auto focal_length = 1.0;

	glm::vec3 origin(0, 0, 0);
	glm::vec3 horizontal(viewport_width, 0, 0);
	glm::vec3 vertical(0, viewport_height, 0);
	auto lower_left_corner = origin - (horizontal / 2.0f) 
		- (vertical / 2.0f) - glm::vec3(0, 0, focal_length);


	//filling renderer buffer
	//TODO: change to take framebuffer size from renderer and be
	//able to set framebuffer size when size changes
	for (int x = 0; x < renderer->getBufferHeight(); x++) {
		for (int y = 0; y < renderer->getBufferWidth(); y++) {
			/*unsigned int color = 0x8a1600ff;
			renderer->updatePixel(x, y, color);*/
			auto u = float(y) / (scrWidth - 1);
			auto v = float(x) / (scrHeight - 1);
			Ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
			//dilemma: should ray_color be coupled to the ray or just a static function returning a color?
			glm::vec3 pixel_color = r.ray_color();

			unsigned int finalColor = Ray::vec3ToRGBA(pixel_color);

			renderer->updatePixel(x, y, finalColor);
		}
	}
}

void Application::run()
{
	//TODO: move to window->shouldClose()
	while (!glfwWindowShouldClose(window->getWindowPtr())) {
		renderer->swap_buffers(0);
		window->frameUpdate();
	}
}

void Application::cleanup()
{
	delete window;
	delete renderer;
	glfwTerminate();
}
