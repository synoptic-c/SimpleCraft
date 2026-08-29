#include"Ore.hpp"
void SimpleCraft::from_json(const nlohmann::json& json, SimpleCraft::OreDefinition& oreDefinition)
{
	json["name"].get_to<std::string>(oreDefinition.name);
	json["threshold"].get_to<float>(oreDefinition.threshold);
	json["depth"].get_to<int>(oreDefinition.depth);
}
SimpleCraft::Ore::Ore(std::string_view path)
{
	std::fstream file(std::string(path), std::ios::in);
	if (!file)
	{
		PRINT_ERROR_FILE("Failed to open file", path);
		return;
	}
	nlohmann::json json = nlohmann::json::parse(file);
	file.close();
	_oreDefinitions = json["oreDefinitions"].get<std::vector<SimpleCraft::OreDefinition>>();
}
const std::vector<SimpleCraft::OreDefinition>& SimpleCraft::Ore::GetOreDefinitions() const
{
	return _oreDefinitions;
}