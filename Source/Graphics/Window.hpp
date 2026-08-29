#pragma once
#include<string>
#include<string_view>
#include<fstream>
#include<nlohmann/json.hpp>
#include<GLFW/glfw3.h>
#include"Util/Log.hpp"
namespace SimpleCraft
{
	class Window
	{
	private:
		GLFWwindow* _window;
	public:
		Window(std::string_view path);
		~Window();
		Window(const SimpleCraft::Window&) = delete;
		SimpleCraft::Window& operator=(const SimpleCraft::Window&) = delete;
		GLFWwindow* GetWindow() const;
		int WindowShouldClose() const;
		void PollEvents() const;
		void SwapBuffers() const;
		int GetKey(int key) const;
		void SetCharCallback() const;
		int GetMouseButton(int button) const;
		double GetCursorPosX() const;
		double GetCursorPosY() const;
		int GetFramebufferSizeX() const;
		int GetFramebufferSizeY() const;
	};
}