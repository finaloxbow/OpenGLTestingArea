#include "Application.h"

#include <glm/glm.hpp>
#include <memory>
#include "Ray.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"

Window* Application::window;
Renderer* Application::renderer;

glm::vec3 ray_color(Ray& r, Hittable& world) {
	HitRecord rec;

	if (world.hit(r, 0, infinity, rec)) {
		return 0.5f * (rec.normal + glm::vec3(1, 1, 1));
	}

	glm::vec3 unit_direction = glm::normalize(r.direction());
	auto t = 0.5f * (unit_direction.y + 1.0f);
	//linear interpolation between the two colors
	return (1.0f - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.5, 0.7, 1.0);
}

void Application::setup()
{
	window = new Window(scrWidth, scrHeight, "Ray Tracing");
	renderer = new Renderer(scrWidth, scrHeight, numChannels, window->getWindowPtr());

	const int samplesPerPixel = 50;

	HittableList world;
	world.add(std::make_shared<Sphere>(glm::vec3(0,0,-1), 0.5));
	world.add(std::make_shared<Sphere>(glm::vec3(0, -100.5, -1), 100));

	Camera cam(scrWidth, scrHeight);


	//filling renderer buffer
	//TODO: change to take framebuffer size from renderer and be
	//able to set framebuffer size when size changes
	for (int x = 0; x < renderer->getBufferHeight(); x++) {
		for (int y = 0; y < renderer->getBufferWidth(); y++) {
			glm::vec3 pixelColor(0,0,0);
			for (int s = 0; s < samplesPerPixel; ++s) {
				auto u = (y + randomFloat()) / (scrWidth - 1);
				auto v = (x + randomFloat()) / (scrHeight - 1);
				Ray r = cam.getRay(u, v);
				pixelColor += ray_color(r, world);
			}

			glm::vec4 rgba = glm::vec4(pixelColor.x, pixelColor.y, pixelColor.z, samplesPerPixel);
			renderer->updatePixel(x, y, rgba, samplesPerPixel);
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
