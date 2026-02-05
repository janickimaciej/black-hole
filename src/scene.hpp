#pragma once

#include "blackHole.hpp"
#include "camera.hpp"
#include "quad.hpp"
#include "scene.hpp"
#include "skybox.hpp"
#include "skyboxPaths.hpp"

#include <glm/glm.hpp>

class Scene
{
public:
	Scene(const glm::ivec2& viewportSize);
	void render() const;
	void updateViewportSize();

	void addPitchCamera(float pitchRad);
	void addYawCamera(float yawRad);
	void zoomCamera(float zoom);

	float getRadiusCamera() const;
	void setRadiusCamera(float radius);
	float getBlackHoleMass() const;
	void setBlackHoleMass(float mass);

private:
	Camera m_camera;
	Quad m_quad{};

	BlackHole m_blackHole{};
	Skybox m_skybox{skyboxPaths};
};
