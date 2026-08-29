#include"BoundManager.hpp"
SimpleCraft::Bound SimpleCraft::BoundManager::LoadBound(std::string_view path)
{
	std::fstream file(std::string(path), std::ios::in);
	if (!file)
	{
		PRINT_ERROR_FILE("Failed to open file", path);
		return SimpleCraft::Bound{};
	}
	nlohmann::json json = nlohmann::json::parse(file);
	file.close();
	return json.get<SimpleCraft::Bound>();
}
SimpleCraft::BoundManager::BoundManager(std::string_view path)
{
	std::fstream file(std::string(path), std::ios::in);
	if (!file)
	{
		PRINT_ERROR_FILE("Failed to open file", path);
		return;
	}
	nlohmann::json json = nlohmann::json::parse(file);
	file.close();
	for (nlohmann::json& json : json["bounds"])
	{
		_bounds.insert({ json["name"].get<std::string>(), LoadBound(json["path"].get<std::string_view>()) });
	}
}
SimpleCraft::Bound SimpleCraft::BoundManager::GetBound(std::string_view name) const
{
	if (std::unordered_map<std::string, SimpleCraft::Bound>::const_iterator it = _bounds.find(std::string(name)); it != _bounds.end())
	{
		return it->second;
	}
	return Bound{};
}