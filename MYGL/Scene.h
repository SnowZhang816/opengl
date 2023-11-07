#pragma once

#include "camera.h"
#include <vector>
#include "Light.h"

class Scene
{
	Scene();
	~Scene();

	void draw(Camera *ca, const std::vector<Light> &lights, Light &spotlight);
};

