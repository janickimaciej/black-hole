#pragma once

#include "scene.hpp"

#include <glm/glm.hpp>

class LeftPanel
{
public:
	static constexpr int width = 250;

	LeftPanel(Scene& scene, const glm::ivec2& windowSize);
	void update();

private:
	Scene& m_scene;
	const glm::ivec2& m_windowSize;

	void updateCamera();

	void separator();
};
