#include"MeshManager.hpp"
SimpleCraft::MeshManager::MeshManager(std::string_view configPath)
{
	std::fstream configFile(std::string(configPath), std::ios::in);
	if (!configFile)
	{
		PRINT_ERROR_FILE("Failed to open file", configPath);
		return;
	}
	nlohmann::json configJson = nlohmann::json::parse(configFile);
	configFile.close();
	for (const nlohmann::json& json : configJson["meshes"])
	{
		_meshes.emplace(json["name"].get<std::string>(), json["path"].get<std::string_view>());
	}
}
const SimpleCraft::Mesh* SimpleCraft::MeshManager::GetMesh(std::string_view name) const
{
	if (std::unordered_map<std::string, SimpleCraft::Mesh>::const_iterator it = _meshes.find(std::string(name)); it != _meshes.end())
	{
		return &it->second;
	}
	return nullptr;
}