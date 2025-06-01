#pragma once

#include "blackHole.hpp"
#include "camera.hpp"
#include "quad.hpp"
#include "scene.hpp"
#include "shaderProgram.hpp"
#include "skybox.hpp"
#include "skyboxPaths.hpp"

#include <glm/glm.hpp>

class Scene
{
public:
	Scene(const glm::ivec2& windowSize);
	void render() const;
	void updateWindowSize();

	void addCameraPitch(float pitchRad);
	void addCameraYaw(float yawRad);
	void zoomCamera(float zoom);

	float getCameraRadius() const;
	void setCameraRadius(float radius);
	float getBlackHoleMass() const;
	void setBlackHoleMass(float mass);

private:
	ShaderProgram m_shaderProgram{"src/shaders/VS.glsl", "src/shaders/FS.glsl"};
	const glm::ivec2& m_windowSize{};

	Camera m_camera;
	Quad m_quad{};

	BlackHole m_blackHole{};
	Skybox m_skybox{skyboxPaths};

	void setAspectRatio(float aspectRatio);
};
