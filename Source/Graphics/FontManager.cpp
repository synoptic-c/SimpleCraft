#include"FontManager.hpp"
SimpleCraft::FontManager::FontManager(std::string_view path) : _quality{}
{
	std::fstream file(std::string(path), std::ios::in);
	if (!file)
	{
		PRINT_ERROR_FILE("Failed to open file", path);
		return;
	}
	nlohmann::json json = nlohmann::json::parse(file);
	_quality = json["quality"].get<float>();
	for (unsigned int i = 0; i < json["fonts"].size(); i++)
	{
		_fonts.emplace(std::piecewise_construct, std::forward_as_tuple(json["fonts"][i]["name"].get<std::string>()), std::forward_as_tuple(json["fonts"][i]["path"].get<std::string_view>(), _quality));
	}
}
const SimpleCraft::Font* SimpleCraft::FontManager::GetFont(std::string_view name) const
{
	if (std::unordered_map<std::string, SimpleCraft::Font>::const_iterator it = _fonts.find(std::string(name)); it != _fonts.end())
	{
		return &it->second;
	}
	return nullptr;
}