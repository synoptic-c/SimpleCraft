#pragma once
#include<string>
#include<string_view>
#include<fstream>
#include<sstream>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"Util/Log.hpp"
namespace SimpleCraft
{
	class Shader
	{
	private:
		unsigned int _program;
		static std::string LoadShader(std::string_view shaderPath);
		static unsigned int CreateShader(std::string_view shaderPath, unsigned int type);
	public:
		Shader(std::string_view vertexPath, std::string_view fragmentPath);
		~Shader();
		Shader(const SimpleCraft::Shader&) = delete;
		SimpleCraft::Shader& operator=(const SimpleCraft::Shader&) = delete;
		Shader(SimpleCraft::Shader&& other) noexcept;
		SimpleCraft::Shader& operator=(SimpleCraft::Shader&& other) noexcept;
		void Use() const;
		void SetMat4(std::string_view name, glm::mat4 value);
		void SetVec2(std::string_view name, glm::vec2 value);
	};
}