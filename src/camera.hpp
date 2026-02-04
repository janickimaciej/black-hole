#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera(const glm::ivec2& viewportSize, float nearPlane, float farPlane, float fovYDeg);

	void use() const;
	glm::mat4 getMatrixInverse() const;
	void updateViewportSize();

	void addPitch(float pitchRad);
	void addYaw(float yawRad);
	void zoom(float zoom);

	float getRadius() const;
	void setRadius(float radius);

private:
	const glm::ivec2& m_viewportSize{};
	float m_nearPlane{};
	float m_farPlane{};
	float m_fovYDeg{};

	glm::vec3 m_targetPos{0, 0, 0};
	float m_pitchRad = 0;
	float m_yawRad = 0;
	float m_radius = 50;

	glm::mat4 m_viewMatrixInverse{1};
	glm::mat4 m_projectionMatrix{1};

	glm::vec3 getPos() const;
	void updateViewMatrix();
	void updateProjectionMatrix();
	void updateShaders() const;
};
