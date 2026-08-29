#include"Window.hpp"
SimpleCraft::Window::Window(std::string_view path) : _window{}
{
	std::fstream file(std::string(path), std::ios::in);
	if (!file)
	{
		PRINT_ERROR_FILE("Failed to open file", path);
		return;
	}
	nlohmann::json json = nlohmann::json::parse(file);
	file.close();
	_window = glfwCreateWindow(json["width"].get<int>(), json["height"].get<int>(), json["title"].get<std::string>().c_str(), nullptr, nullptr);
	if (!_window)
	{
		PRINT_ERROR("Failed to create window");
		return;
	}
	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height)
		{
			glViewport(int{}, int{}, width, height);
		});
}
SimpleCraft::Window::~Window()
{
	if (_window)
	{
		glfwDestroyWindow(_window);
	}
}
GLFWwindow* SimpleCraft::Window::GetWindow() const
{
	if (_window)
	{
		return _window;
	}
	return nullptr;
}
int SimpleCraft::Window::WindowShouldClose() const
{
	if (_window)
	{
		return glfwWindowShouldClose(_window);
	}
	return 1;
}
void SimpleCraft::Window::PollEvents() const
{
	if (_window)
	{
		glfwPollEvents();
	}
}
void SimpleCraft::Window::SwapBuffers() const
{
	if (_window)
	{
		glfwSwapBuffers(_window);
	}
}
int SimpleCraft::Window::GetKey(int key) const
{
	if (_window)
	{
		return glfwGetKey(_window, key) == GLFW_PRESS;
	}
	return -1;
}
int SimpleCraft::Window::GetMouseButton(int button) const
{
	if (_window)
	{
		return glfwGetMouseButton(_window, button) == GLFW_PRESS;
	}
	return -1;
}
double SimpleCraft::Window::GetCursorPosX() const
{
	if (_window)
	{
		double xpos;
		glfwGetCursorPos(_window, &xpos, nullptr);
		return xpos;
	}
	return double{};
}
double SimpleCraft::Window::GetCursorPosY() const
{
	if (_window)
	{
		double ypos;
		glfwGetCursorPos(_window, nullptr, &ypos);
		return ypos;
	}
	return double{};
}
int SimpleCraft::Window::GetFramebufferSizeX() const
{
	if (_window)
	{
		int width;
		glfwGetFramebufferSize(_window, &width, nullptr);
		return width;
	}
	return int{};
}
int SimpleCraft::Window::GetFramebufferSizeY() const
{
	if (_window)
	{
		int height;
		glfwGetFramebufferSize(_window, nullptr, &height);
		return height;
	}
	return int{};
}