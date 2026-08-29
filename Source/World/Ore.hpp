#pragma once
#include<string>
#include<string_view>
#include<vector>
#include<fstream>
#include<nlohmann/json.hpp>
#include"Util/Log.hpp"
namespace SimpleCraft
{
	struct OreDefinition
	{
		std::string name;
		float threshold{};
		int depth{};
	};
	void from_json(const nlohmann::json& json, SimpleCraft::OreDefinition& oreDefinition);
	class Ore
	{
	private:
		std::vector<SimpleCraft::OreDefinition> _oreDefinitions;
	public:
		Ore(std::string_view path);
		const std::vector<SimpleCraft::OreDefinition>& GetOreDefinitions() const;
	};
}