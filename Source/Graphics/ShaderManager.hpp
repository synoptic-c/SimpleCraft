#pragma once
#include<string>
#include<string_view>
#include<unordered_map>
#include<fstream>
#include<nlohmann/json.hpp>
#include"Graphics/Shader.hpp"
#include"Util/Log.hpp"
namespace SimpleCraft
{
	class ShaderManager
	{
	private:
		std::unordered_map<std::string, SimpleCraft::Shader> _shaders;
	public:
		ShaderManager(std::string_view configPath);
		const SimpleCraft::Shader* GetShader(std::string_view name) const;
		SimpleCraft::Shader* GetShader(std::string_view name);
	};
}