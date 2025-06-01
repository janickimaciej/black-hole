#include "scene.hpp"

#include <string>

static constexpr float fovYDeg = 60.0f;
static constexpr float nearPlane = 0.1f;
static constexpr float farPlane = 1000.0f;

static constexpr glm::vec3 initialBlackHolePosition{0, 0, 0};
static constexpr float initialBlackHoleMass = 1;

Scene::Scene(const glm::ivec2& windowSize) :
	m_windowSize{windowSize},
	m_camera{fovYDeg, static_cast<float>(windowSize.x) / windowSize.y, nearPlane, farPlane,
		m_shaderProgram},
	m_blackHole{initialBlackHolePosition, initialBlackHoleMass}
{ }

void Scene::render() const
{
	static constexpr glm::vec3 backgroundColor{0.1f, 0.1f, 0.1f};
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_camera.use();

	m_shaderProgram.use();
	m_shaderProgram.setUniform("blackHole.position", m_blackHole.position);
	m_shaderProgram.setUniform("blackHole.mass", m_blackHole.mass);

	m_skybox.use();

	m_quad.render();
}

void Scene::updateWindowSize()
{
	setAspectRatio(static_cast<float>(m_windowSize.x) / m_windowSize.y);
}

void Scene::addCameraPitch(float pitchRad)
{
	m_camera.addPitch(pitchRad);
}

void Scene::addCameraYaw(float yawRad)
{
	m_camera.addYaw(yawRad);
}

void Scene::zoomCamera(float zoom)
{
	m_camera.zoom(zoom);
}

float Scene::getCameraRadius() const
{
	return m_camera.getRadius();
}

void Scene::setCameraRadius(float radius)
{
	m_camera.setRadius(radius);
}

float Scene::getBlackHoleMass() const
{
	return m_blackHole.mass;
}

void Scene::setBlackHoleMass(float mass)
{
	m_blackHole.mass = mass;
}

void Scene::setAspectRatio(float aspectRatio)
{
	m_camera.setAspectRatio(aspectRatio);
}
