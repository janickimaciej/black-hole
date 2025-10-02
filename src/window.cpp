#include "window.hpp"

#include "guis/leftPanel.hpp"

#include <string>

Window::Window(const glm::ivec2& initialSize) :
	m_size{initialSize}
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	static const std::string windowTitle = "black-hole";
	m_windowPtr = glfwCreateWindow(initialSize.x, initialSize.y, windowTitle.c_str(), nullptr,
		nullptr);
	glfwSetWindowUserPointer(m_windowPtr, this);
	glfwMakeContextCurrent(m_windowPtr);
	glfwSwapInterval(1);

	glfwSetFramebufferSizeCallback(m_windowPtr, resizeCallback);
	glfwSetCursorPosCallback(m_windowPtr, cursorMovementCallback);
	glfwSetScrollCallback(m_windowPtr, scrollCallback);

	gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
}

Window::~Window()
{
	glfwTerminate();
}

const glm::ivec2& Window::size() const
{
	return m_size;
}

void Window::setWindowData(Scene& scene)
{
	m_scene = &scene;
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(m_windowPtr);
}

void Window::swapBuffers() const
{
	glfwSwapBuffers(m_windowPtr);
}

void Window::pollEvents() const
{
	glfwPollEvents();
}

GLFWwindow* Window::getPtr()
{
	return m_windowPtr;
}

void Window::resizeCallback(GLFWwindow* windowPtr, int width, int height)
{
	if (width == 0 || height == 0)
	{
		return;
	}

	Window* window = static_cast<Window*>(glfwGetWindowUserPointer(windowPtr));

	window->m_size = {width, height};
	window->m_scene->updateWindowSize();
	glViewport(0, 0, width, height);
}

void Window::cursorMovementCallback(GLFWwindow* windowPtr, double x, double y)
{
	Window* window = static_cast<Window*>(glfwGetWindowUserPointer(windowPtr));
	if (window->isCursorInGUI())
	{
		return;
	}

	glm::vec2 currentPos{static_cast<float>(x), static_cast<float>(y)};
	glm::vec2 offset = currentPos - window->m_lastCursorPos;
	window->m_lastCursorPos = currentPos;

	if (glfwGetMouseButton(windowPtr, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		static constexpr float sensitivity = 0.002f;
		window->m_scene->addCameraPitch(-sensitivity * offset.y);
		window->m_scene->addCameraYaw(sensitivity * offset.x);
	}
}

void Window::scrollCallback(GLFWwindow* windowPtr, double, double yOffset)
{
	Window* window = static_cast<Window*>(glfwGetWindowUserPointer(windowPtr));
	if (window->isCursorInGUI())
	{
		return;
	}

	static constexpr float sensitivity = 1.1f;
	window->m_scene->zoomCamera(std::pow(sensitivity, static_cast<float>(yOffset)));
}

bool Window::isCursorInGUI()
{
	double x{};
	double y{};
	glfwGetCursorPos(m_windowPtr, &x, &y);
	glm::vec2 cursorPos{static_cast<float>(x), static_cast<float>(y)};
	return cursorPos.x <= LeftPanel::width;
}
