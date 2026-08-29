#pragma once
#include<string>
#include<string_view>
#include<fstream>
#include<unordered_map>
#include<nlohmann/json.hpp>
#include<glm/glm.hpp>
#include"Util/Log.hpp"
namespace SimpleCraft
{
	struct AtlasDefinition
	{
		glm::vec2 uvOffset{};
		glm::vec2 uvIndex{};
		glm::vec2 uvScale{};
	};
	void from_json(const nlohmann::json& json, SimpleCraft::AtlasDefinition& atlasDefinition);
	class Atlas
	{
	private:
		std::unordered_map<std::string, SimpleCraft::AtlasDefinition> _atlasDefinitions;
	public:
		Atlas(std::string_view path);
		glm::vec2 GetUvOffset(std::string_view name) const;
		glm::vec2 GetUvIndex(std::string_view name) const;
		glm::vec2 GetUvScale(std::string_view name) const;
	};
}