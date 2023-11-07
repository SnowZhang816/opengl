#pragma once

#include <string>

class Texture
{
public:
	unsigned int ID;
	std::string name;
	std::string path;

	Texture(const char* imagePath, std::string na = "texture_diffuse");
	Texture(unsigned int id);
	~Texture();

	void use(unsigned int id);
};

