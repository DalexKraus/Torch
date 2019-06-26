#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>

class Texture
{
private:
	int _textureId;
	int _width;
	int _height;
public:
	Texture(int texId, int width, int height);
	static Texture* readTextureFromFile(const std::string fileName);
	int* getId();
	int* getWidth();
	int* getHeight();
};

#endif