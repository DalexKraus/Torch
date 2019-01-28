#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture.h"

Texture::Texture(int texId, int width, int height)
{
	_textureId = texId;
	_width = width;
	_height = height;
}

int* Texture::getId()
{
	return &_textureId;
}

int* Texture::getWidth()
{
	return &_width;
}

int* Texture::getHeight()
{
	return &_height;
}

Texture* Texture::readTextureFromFile(const std::string fileName)
{
	unsigned int texId;
	int width, height, numChannels;

	//Create a texture and bind it
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	//set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			
	//Read image data from file using stb_image.h
	unsigned char *data = stbi_load(fileName.c_str(), &width, &height, &numChannels, 0);

	//Check if data isn't null
	if (data)
	{
		//Fill texture with image data and generate mipmaps
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture '" << fileName.c_str() << "'!" << std::endl;
		return NULL;
	}

	//Free the image data
	stbi_image_free(data);

	//Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//Create a new texture instance
	Texture* texture = new Texture(texId, width, height);
	return texture;
}
