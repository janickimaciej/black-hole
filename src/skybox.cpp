#include "skybox.hpp"

#include <glad/glad.h>
#include <stb_image.h>

#include <iostream>

Skybox::Skybox(const std::vector<std::string>& paths)
{
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);

	int width{};
	int height{};
	int channels{};
	for (int i = 0; i < paths.size(); ++i)
	{
		unsigned char* data = stbi_load(paths[i].c_str(), &width, &height, &channels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGBA,
				GL_UNSIGNED_BYTE, data);
		}
		else
		{
			std::cerr << "Error loading texture:\n" << paths[i] << '\n';
		}
		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

Skybox::~Skybox()
{
	glDeleteTextures(1, &m_textureID);
}

void Skybox::use() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
}
