#pragma once
#include<memory>
#include<string>
#include<string_view>
#include<fstream>
#include<cstdint>
#include<cmath>
#include<unordered_map>
#include<nlohmann/json.hpp>
#include<FastNoiseLite/FastNoiseLite.h>
#include<glm/glm.hpp>
#include"World/Structure.hpp"
#include"Ore.hpp"
#include"Chunk.hpp"
#include"Util/Log.hpp"
namespace SimpleCraft
{
	class World
	{
	private:
		std::unordered_map<int64_t, SimpleCraft::Chunk> _chunks;
		int _chunkCountWidth;
		int _chunkCountHeight;
		int _chunkWidth;
		int _chunkHeight;
		float _surfaceFrequency;
		float _surfaceAmplitude;
		float _oreFrequency;
		int _dirtDepth;
		std::unique_ptr<SimpleCraft::Structure> _structure;
		std::unique_ptr<SimpleCraft::Ore> _ore;
		FastNoiseLite _surfaceNoise;
		FastNoiseLite _oreNoise;
		static int64_t MakeKey(int chunkX, int chunkY);
		static void DecodeKey(int64_t key, int& chunkX, int& chunkY);
	public:
		World(std::string_view worldConfigPath, std::string_view structureConfigPath, std::string_view oreDataPath);
		void GenerateChunk(const std::unordered_map<std::string, int>& tileDefinitions, glm::vec2 playerPosition);
		void LoadChunk(glm::vec2 playerPosition);
		void UnloadChunk(glm::vec2 playerPosition);
		int GetTile(glm::vec2 worldPosition);
		void SetTile(glm::vec2 worldPosition, int value);
	};
}