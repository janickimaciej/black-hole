#pragma once

#include "scene.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

class Window
{
public:
	Window(const glm::ivec2& initialSize);
	~Window();

	const glm::ivec2& size() const;
	void setWindowData(Scene& scene);
	bool shouldClose() const;
	void swapBuffers() const;
	void pollEvents() const;
	GLFWwindow* getPtr();

private:
	GLFWwindow* m_windowPtr{};
	glm::ivec2 m_size{};
	Scene* m_scene{};

	glm::vec2 m_lastCursorPos{};

	static void resizeCallback(GLFWwindow* windowPtr, int width, int height);
	static void cursorMovementCallback(GLFWwindow* windowPtr, double x, double y);
	static void scrollCallback(GLFWwindow* windowPtr, double, double yOffset);
};
