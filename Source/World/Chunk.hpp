#pragma once
#include<vector>
#include<unordered_map>
#include<string>
#include<nlohmann/json.hpp>
#include<FastNoiseLite/FastNoiseLite.h>
#include"World/Structure.hpp"
#include"Ore.hpp"
namespace SimpleCraft
{
	class Chunk
	{
	private:
		std::vector<int> _data;
		int _width;
		int _height;
		static int GetTileDefinition(const std::unordered_map<std::string, int>& tileDefinitions, std::string_view name);
		static const SimpleCraft::StructureData* GetStructureData(const std::unordered_map<std::string, SimpleCraft::StructureData>& structures, std::string_view name);
	public:
		Chunk(const std::unordered_map<std::string, SimpleCraft::StructureData>& structures, const FastNoiseLite& surfaceNoise, const FastNoiseLite& oreNoise, const std::vector<SimpleCraft::OreDefinition>& oreDefinitions, const std::unordered_map<std::string, int>& tileDefinitions, float surfaceFrequency, float surfaceAmplitude, float oreFrequency, int dirtDepth, int width, int height, int chunkX, int chunkY);
		int GetSurfaceY(const FastNoiseLite& surfaceNoise, int worldX, float surfaceFrequency, float surfaceAmplitude);
//		void StructurePlace(const SimpleCraft::StructureData* structureData, const std::unordered_map<std::string, int>& tileDefinitions, int chunkX, int chunkY);
		int GetTile(int localX, int localY) const;
		void SetTile(int localX, int localY, int value);
	};
}
