#include "scene.hpp"

#include "shaderPrograms.hpp"

#include <glad/glad.h>

#include <string>

static constexpr float nearPlane = 0.1f;
static constexpr float farPlane = 1000.0f;
static constexpr float fovYDeg = 60.0f;

static constexpr glm::vec3 initialBlackHolePos{0, 0, 0};
static constexpr float initialBlackHoleMass = 1;

Scene::Scene(const glm::ivec2& viewportSize) :
	m_viewportSize{viewportSize},
	m_camera{viewportSize, nearPlane, farPlane, fovYDeg},
	m_blackHole{initialBlackHolePos, initialBlackHoleMass}
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
}

void Scene::render() const
{
	static constexpr glm::vec3 backgroundColor{0.1f, 0.1f, 0.1f};
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_camera.use();

	ShaderPrograms::hole->use();
	ShaderPrograms::hole->setUniform("blackHole.pos", m_blackHole.pos);
	ShaderPrograms::hole->setUniform("blackHole.mass", m_blackHole.mass);

	m_skybox.use();

	m_quad.render();
}

void Scene::updateViewportSize()
{
	m_camera.updateViewportSize();
}

void Scene::addPitchCamera(float pitchRad)
{
	m_camera.addPitch(pitchRad);
}

void Scene::addYawCamera(float yawRad)
{
	m_camera.addYaw(yawRad);
}

void Scene::zoomCamera(float zoom)
{
	m_camera.zoom(zoom);
}

float Scene::getRadiusCamera() const
{
	return m_camera.getRadius();
}

void Scene::setRadiusCamera(float radius)
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
