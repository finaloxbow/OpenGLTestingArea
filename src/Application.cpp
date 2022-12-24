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

HittableList randomScene() {
	HittableList world;

	glm::vec3 groundColor(0.5f, 0.5f, 0.5f);
	auto groundMaterial = new Lambertian(groundColor);
	world.add(std::make_shared<Sphere>(glm::vec3(0, -1000, 0), 1000, groundMaterial));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto chooseMat = randomFloat();
			glm::vec3 center(a + 0.9*randomFloat(), 0.2, b + 0.9*randomFloat());

			glm::vec3 tmp = center - glm::vec3(4, 0.2, 0);
			if (sqrt(length_squared(tmp)) > 0.9) {
				Material* sphereMaterial;

				if (chooseMat < 0.8) {
					auto rand1 = random();
					auto rand2 = random();
					glm::vec3 albedo(rand1.x * rand2.x, rand1.y * rand2.y, rand1.z * rand2.z);

					sphereMaterial = new Lambertian(albedo);
					world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
				}
				else if (chooseMat < 0.95) {
					auto albedo = random(0.5, 1);
					auto fuzz = randomFloat(0, 0.5);
					sphereMaterial = new Metal(albedo, fuzz);
					world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
				}
				else {
					sphereMaterial = new Dielectric(1.5f);
					world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
				}
			}
			
		}
	}

	auto material1 = new Dielectric(1.5f);
	world.add(std::make_shared<Sphere>(glm::vec3(0,1,0), 1.0f, material1));

	glm::vec3 color2(0.4f, 0.2f, 0.1f);
	auto material2 = new Lambertian(color2);
	world.add(std::make_shared<Sphere>(glm::vec3(-4, 1, 0), 1.0f, material2));

	glm::vec3 color3(0.7f, 0.6f, 0.5f);
	auto material3 = new Metal(color3, 0.0f);
	world.add(std::make_shared<Sphere>(glm::vec3(4, 1, 0), 1.0f, material3));

	return world;
}

void Application::setup()
{
	window = new Window(scrWidth, scrHeight, "Ray Tracing");
	renderer = new Renderer(scrWidth, scrHeight, numChannels, window->getWindowPtr());

	const auto aspectRatio = float(scrWidth) / float(scrHeight);
	const int samplesPerPixel = 30;
	const int maxDepth = 25;

	auto world = randomScene();
	
	//TODO: create camera here
	glm::vec3 lookfrom(13,2,3);
	glm::vec3 lookat(0,0,0);
	glm::vec3 vup(0,1,0);
	auto focusDist = 10.0f;
	auto aperture = 0.1f;
	auto vfov = 20;

	Camera cam(lookfrom, lookat, vup, vfov, aspectRatio, aperture, focusDist);

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
