#include "camera.hpp"

#include <glm/gtc/constants.hpp>

Camera::Camera(float fovYDeg, float aspectRatio, float nearPlane, float farPlane,
	const ShaderProgram& shaderProgram) :
	m_aspectRatio{aspectRatio},
	m_fovYDeg{fovYDeg},
	m_nearPlane{nearPlane},
	m_farPlane{farPlane},
	m_shaderProgram{shaderProgram}
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

void Camera::setAspectRatio(float aspectRatio)
{
	m_aspectRatio = aspectRatio;

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

glm::vec3 Camera::getPosition() const
{
	return glm::vec3{m_viewMatrixInverse[3][0], m_viewMatrixInverse[3][1],
		m_viewMatrixInverse[3][2]};
}

void Camera::updateViewMatrix()
{
	glm::vec3 position = m_targetPosition + m_radius *
		glm::vec3
		{
			-std::cos(m_pitchRad) * std::sin(m_yawRad),
			-std::sin(m_pitchRad),
			std::cos(m_pitchRad) * std::cos(m_yawRad)
		};

	glm::vec3 direction = glm::normalize(position - m_targetPosition);
	glm::vec3 right = glm::normalize(glm::cross(glm::vec3{0, 1, 0}, direction));
	glm::vec3 up = glm::cross(direction, right);

	m_viewMatrixInverse =
	{
		right.x, right.y, right.z, 0,
		up.x, up.y, up.z, 0,
		direction.x, direction.y, direction.z, 0,
		position.x, position.y, position.z, 1
	};
}

void Camera::updateProjectionMatrix()
{
	float fovYRad = glm::radians(m_fovYDeg);
	float cot = std::cos(fovYRad / 2) / std::sin(fovYRad / 2);

	m_projectionMatrix =
	{
		cot / m_aspectRatio, 0, 0, 0,
		0, cot, 0, 0,
		0, 0, -(m_farPlane + m_nearPlane) / (m_farPlane - m_nearPlane), -1,
		0, 0, -2 * m_farPlane * m_nearPlane / (m_farPlane - m_nearPlane), 0
	};
}

void Camera::updateShaders() const
{
	m_shaderProgram.use();
	m_shaderProgram.setUniform("nearPlane", m_nearPlane);
	m_shaderProgram.setUniform("farPlane", m_farPlane);
	m_shaderProgram.setUniform("cameraPosition", getPosition());
	m_shaderProgram.setUniform("projectionViewInverse", getMatrixInverse());
}
