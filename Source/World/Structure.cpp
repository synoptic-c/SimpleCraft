#include"Structure.hpp"
SimpleCraft::Structure::Structure(std::string_view configPath)
{
	std::fstream file(std::string(configPath), std::ios::in);
	if (!file)
	{
		PRINT_ERROR_FILE("Failed to open file", configPath);
		return;
	}
	nlohmann::json configJson = nlohmann::json::parse(file);
	file.close();
	for (unsigned int i = 0; i < configJson["structures"].size(); i++)
	{
		file.open(std::string(configJson["structures"][i].get<std::string_view>()), std::ios::in);
		if (file)
		{
			nlohmann::json json = nlohmann::json::parse(file);
			_structures.emplace(std::piecewise_construct, std::forward_as_tuple(json["name"].get<std::string>()), std::forward_as_tuple(SimpleCraft::StructureData{ json["width"].get<unsigned int>(), json["height"].get<unsigned int>(), json["tiles"].get<std::vector<std::string>>() }));
		}
		file.close();
	}
}
const SimpleCraft::StructureData* SimpleCraft::Structure::GetStructure(std::string_view name) const
{
	if (std::unordered_map<std::string, SimpleCraft::StructureData>::const_iterator it = _structures.find(std::string(name)); it != _structures.end())
	{
		return &it->second;
	}
	return nullptr;
}
const std::unordered_map<std::string, SimpleCraft::StructureData>& SimpleCraft::Structure::GetStructures() const
{
	return _structures;
}