#pragma once
class Texture
{
public:
	unsigned int ID;

	Texture(const char* imagePath, unsigned int format);
	~Texture();

	void use(unsigned int id);
};

