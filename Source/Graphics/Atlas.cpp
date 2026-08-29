#include"Atlas.hpp"
void SimpleCraft::from_json(const nlohmann::json& json, SimpleCraft::AtlasDefinition& atlasDefinition)
{
	json["uvOffset"]["x"].get_to<float>(atlasDefinition.uvOffset.x);
	json["uvOffset"]["y"].get_to<float>(atlasDefinition.uvOffset.y);
	json["uvIndex"]["x"].get_to<float>(atlasDefinition.uvIndex.x);
	json["uvIndex"]["y"].get_to<float>(atlasDefinition.uvIndex.y);
	json["uvScale"]["x"].get_to<float>(atlasDefinition.uvScale.x);
	json["uvScale"]["y"].get_to<float>(atlasDefinition.uvScale.y);
}
SimpleCraft::Atlas::Atlas(std::string_view path)
{
	std::fstream file(std::string(path), std::ios::in);
	if (!file)
	{
		PRINT_ERROR_FILE("Failed to open file", path);
		return;
	}
	nlohmann::json json = nlohmann::json::parse(file);
	file.close();
	_atlasDefinitions = json.get<std::unordered_map<std::string, SimpleCraft::AtlasDefinition>>();
}
glm::vec2 SimpleCraft::Atlas::GetUvOffset(std::string_view name) const
{
	if (std::unordered_map<std::string, SimpleCraft::AtlasDefinition>::const_iterator it = _atlasDefinitions.find(std::string(name)); it != _atlasDefinitions.end())
	{
		return it->second.uvOffset;
	}
	return glm::vec2{};
}
glm::vec2 SimpleCraft::Atlas::GetUvIndex(std::string_view name) const
{
	if (std::unordered_map<std::string, SimpleCraft::AtlasDefinition>::const_iterator it = _atlasDefinitions.find(std::string(name)); it != _atlasDefinitions.end())
	{
		return it->second.uvIndex;
	}
	return glm::vec2{};
}
glm::vec2 SimpleCraft::Atlas::GetUvScale(std::string_view name) const
{
	if (std::unordered_map<std::string, SimpleCraft::AtlasDefinition>::const_iterator it = _atlasDefinitions.find(std::string(name)); it != _atlasDefinitions.end())
	{
		return it->second.uvScale;
	}
	return glm::vec2{};
}