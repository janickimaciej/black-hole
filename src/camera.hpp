#pragma once

#include "shaderProgram.hpp"

#include <glm/glm.hpp>

class Camera
{
public:
	Camera(float fovYDeg, float aspectRatio, float nearPlane, float farPlane,
		const ShaderProgram& shaderProgram);
	void use() const;
	glm::mat4 getMatrixInverse() const;
	void setAspectRatio(float aspectRatio);

	void addPitch(float pitchRad);
	void addYaw(float yawRad);
	void zoom(float zoom);

	float getRadius() const;
	void setRadius(float radius);

private:
	glm::vec3 m_targetPosition{0, 0, 0};
	float m_radius = 50;

	float m_aspectRatio{};
	float m_fovYDeg{};
	float m_nearPlane{};
	float m_farPlane{};

	float m_pitchRad = 0;
	float m_yawRad = 0;

	glm::mat4 m_viewMatrixInverse{1};
	glm::mat4 m_projectionMatrix{1};

	const ShaderProgram& m_shaderProgram;

	glm::vec3 getPosition() const;
	void updateViewMatrix();
	void updateProjectionMatrix();
	void updateShaders() const;
};
