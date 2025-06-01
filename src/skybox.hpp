#pragma once

#include <string>
#include <vector>

class Skybox
{
public:
	Skybox(const std::vector<std::string>& paths);
	~Skybox();
	void use() const;

private:
	unsigned int m_textureID{};
};
