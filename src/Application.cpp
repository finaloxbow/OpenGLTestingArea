#include "Application.h"

#include <glm/glm.hpp>
#include <memory>
#include "Ray.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

Window* Application::window;
Renderer* Application::renderer;

glm::vec3 ray_color(Ray& r, Hittable& world, int depth) {
	HitRecord rec;

	if (depth <= 0)
		return glm::vec3(0,0,0);

	if (world.hit(r, 0.001f, infinity, rec)) {
		/*glm::vec3 target = rec.point + rec.normal + randomInUnitSphere();
		Ray newRay(rec.point, target - rec.point);
		return 0.5f * ray_color(newRay, world, depth - 1);*/
		glm::vec3 atten(0, 0, 0);
		Ray scattered(atten, atten);
		if (rec.mat_ptr->scatter(r, rec, atten, scattered))
			return atten * ray_color(scattered, world, depth - 1);
		return glm::vec3(0,0,0);
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

	const int samplesPerPixel = 25;
	const int maxDepth = 10;

	HittableList world;
	
	glm::vec3 groundColor(0.8f,0.8f, 0.0f);
	glm::vec3 centerColor(0.7f, 0.3f, 0.3f);
	glm::vec3 leftColor(0.8f, 0.8f, 0.8f);
	glm::vec3 rightColor(0.8f, 0.6f, 0.2f);

	auto material_ground = new Lambertian(groundColor);
	auto material_center = new Lambertian(centerColor);
	auto material_left = new Dielectric(1.5f);
	auto material_right = new Metal(rightColor);


	world.add(std::make_shared<Sphere>(glm::vec3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(std::make_shared<Sphere>(glm::vec3(0.0, 0.0, -1.0), 0.5, material_center));
	world.add(std::make_shared<Sphere>(glm::vec3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.add(std::make_shared<Sphere>(glm::vec3(-1.0, 0.0, -1.0), -0.45, material_left));
	world.add(std::make_shared<Sphere>(glm::vec3(1.0, 0.0, -1.0), 0.5, material_right));

	
	//TODO: create camera here
	glm::vec3 lookfrom(3,3,2);
	glm::vec3 lookat(0,0,-1);
	glm::vec3 vup(0,1,0);
	glm::vec3 focal = lookfrom - lookat;
	auto focusDist = sqrt(length_squared(focal));
	auto aperture = 2.0;

	Camera cam(lookfrom, lookat, vup, 20, float(scrWidth) / float(scrHeight), aperture, focusDist);

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
				pixelColor += ray_color(r, world, maxDepth);
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
