#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "Render.h"
#include "Camera.h"
#include "Light.h"

#include <vector>

class Model;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCords;
};

class Mesh : public Render
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Model *model);
	~Mesh();

	void draw(Camera *ca, const std::vector<Light> &lights, Light &spotlight);
	void drawSimple(Camera *ca);
private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	Model *model;
};

