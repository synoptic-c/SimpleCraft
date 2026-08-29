#include"ShaderManager.hpp"
SimpleCraft::ShaderManager::ShaderManager(std::string_view configPath)
{
	std::fstream configFile(std::string(configPath), std::ios::in);
	if (!configFile)
	{
		PRINT_ERROR_FILE("Failed to open file", configPath);
		return;
	}
	nlohmann::json configJson = nlohmann::json::parse(configFile);
	configFile.close();
	for (const nlohmann::json& json : configJson["shaders"])
	{
		_shaders.emplace(std::piecewise_construct, std::forward_as_tuple(json["name"].get<std::string>()), std::forward_as_tuple(json["vertexPath"].get<std::string_view>(), json["fragmentPath"].get<std::string_view>()));
	}
}
const SimpleCraft::Shader* SimpleCraft::ShaderManager::GetShader(std::string_view name) const
{
	if (std::unordered_map<std::string, SimpleCraft::Shader>::const_iterator it = _shaders.find(std::string(name)); it != _shaders.end())
	{
		return &it->second;
	}
	return nullptr;
}
SimpleCraft::Shader* SimpleCraft::ShaderManager::GetShader(std::string_view name)
{
	if (std::unordered_map<std::string, SimpleCraft::Shader>::iterator it = _shaders.find(std::string(name)); it != _shaders.end())
	{
		return &it->second;
	}
	return nullptr;
}