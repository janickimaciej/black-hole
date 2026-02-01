#pragma once

#include "scene.hpp"

#include <glm/glm.hpp>

class LeftPanel
{
public:
	static constexpr int width = 200;

	LeftPanel(Scene& scene, const glm::ivec2& viewportSize);
	void update();

private:
	Scene& m_scene;
	const glm::ivec2& m_viewportSize;

	void updateCamera();

	void separator();
};
