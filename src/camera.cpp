#include "camera.hpp"

#include "shaderPrograms.hpp"

#include <glm/gtc/constants.hpp>

Camera::Camera(const glm::ivec2& viewportSize, float nearPlane, float farPlane, float fovYDeg) :
	m_viewportSize{viewportSize},
	m_nearPlane{nearPlane},
	m_farPlane{farPlane},
	m_fovYDeg{fovYDeg}
{
	updateViewMatrix();
	updateProjectionMatrix();
}

void Camera::use() const
{
	updateShaders();
}

glm::mat4 Camera::getMatrixInverse() const
{
	return m_viewMatrixInverse * glm::inverse(m_projectionMatrix);
}

void Camera::updateViewportSize()
{
	updateProjectionMatrix();
}

void Camera::addPitch(float pitchRad)
{
	m_pitchRad += pitchRad;

	static constexpr float bound = glm::radians(89.0f);
	if (m_pitchRad < -bound)
	{
		m_pitchRad = -bound;
	}
	if (m_pitchRad > bound)
	{
		m_pitchRad = bound;
	}

	updateViewMatrix();
}

void Camera::addYaw(float yawRad)
{
	m_yawRad += yawRad;

	static constexpr float pi = glm::pi<float>();
	while (m_yawRad < -pi)
	{
		m_yawRad += 2 * pi;
	}
	while (m_yawRad >= pi)
	{
		m_yawRad -= 2 * pi;
	}

	updateViewMatrix();
}

void Camera::zoom(float zoom)
{
	m_radius /= zoom;

	updateViewMatrix();
}

float Camera::getRadius() const
{
	return m_radius;
}

void Camera::setRadius(float radius)
{
	m_radius = radius;

	updateViewMatrix();
}

glm::vec3 Camera::getPos() const
{
	return m_targetPos + m_radius *
		glm::vec3
		{
			-std::cos(m_pitchRad) * std::sin(m_yawRad),
			-std::sin(m_pitchRad),
			std::cos(m_pitchRad) * std::cos(m_yawRad)
		};
}

void Camera::updateViewMatrix()
{
	glm::vec3 pos = getPos();

	glm::vec3 direction = glm::normalize(pos - m_targetPos);
	glm::vec3 right = glm::normalize(glm::cross(glm::vec3{0, 1, 0}, direction));
	glm::vec3 up = glm::cross(direction, right);

	m_viewMatrixInverse =
	{
		right.x, right.y, right.z, 0,
		up.x, up.y, up.z, 0,
		direction.x, direction.y, direction.z, 0,
		pos.x, pos.y, pos.z, 1
	};
}

void Camera::updateProjectionMatrix()
{
	float aspectRatio = static_cast<float>(m_viewportSize.x) / m_viewportSize.y;
	float fovYRad = glm::radians(m_fovYDeg);
	float cot = std::cos(fovYRad / 2) / std::sin(fovYRad / 2);

	m_projectionMatrix =
	{
		cot / aspectRatio, 0, 0, 0,
		0, cot, 0, 0,
		0, 0, -(m_farPlane + m_nearPlane) / (m_farPlane - m_nearPlane), -1,
		0, 0, -2 * m_farPlane * m_nearPlane / (m_farPlane - m_nearPlane), 0
	};
}

void Camera::updateShaders() const
{
	ShaderPrograms::hole->use();
	ShaderPrograms::hole->setUniform("nearPlane", m_nearPlane);
	ShaderPrograms::hole->setUniform("farPlane", m_farPlane);
	ShaderPrograms::hole->setUniform("cameraPos", getPos());
	ShaderPrograms::hole->setUniform("projectionViewInverse", getMatrixInverse());
}
