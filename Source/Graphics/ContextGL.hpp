#pragma once
#include<string>
#include<string_view>
#include<fstream>
#include<nlohmann/json.hpp>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"Util/Log.hpp"
namespace SimpleCraft
{
	class ContextGL
	{
	public:
		ContextGL(std::string_view path);
		~ContextGL();
		void LoadGLLoader();
	};
}