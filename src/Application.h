#pragma once

#include "Window.h"
#include "Renderer.h"

//16 : 9 aspect ratio
static auto scrWidth = 1280;
static auto scrHeight = 720;
static constexpr auto numChannels = 4;

class Application {
public:
	static void setup();
	static void run();
	static void cleanup();

private:
	static Window* window;
	static Renderer* renderer;
};