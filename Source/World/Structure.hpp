#pragma once
#include<unordered_map>
#include<vector>
#include<string>
#include<string_view>
#include<fstream>
#include<nlohmann/json.hpp>
#include"Util/Log.hpp"
namespace SimpleCraft
{
	struct StructureData
	{
		unsigned int width;
		unsigned int height;
		std::vector<std::string> tiles;
	};
	class Structure
	{
	private:
		std::unordered_map<std::string, SimpleCraft::StructureData> _structures;
	public:
		Structure(std::string_view configPath);
		const SimpleCraft::StructureData* GetStructure(std::string_view name) const;
		const std::unordered_map<std::string, SimpleCraft::StructureData>& GetStructures() const;
	};
}