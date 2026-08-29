#include"World.hpp"
int64_t SimpleCraft::World::MakeKey(int chunkX, int chunkY)
{
	return ((uint64_t)(uint32_t) chunkX << 32) | (uint64_t)(uint32_t)chunkY;
}
void SimpleCraft::World::DecodeKey(int64_t key, int& chunkX, int& chunkY)
{
	chunkX = (int)(int32_t)(key >> 32);
	chunkY = (int)(int32_t)(key & 0xFFFFFFFFULL);
}
SimpleCraft::World::World(std::string_view worldConfigPath, std::string_view structureConfigPath, std::string_view oreDataPath) : _chunkCountWidth{}, _chunkCountHeight{}, _chunkWidth{}, _chunkHeight{}, _surfaceFrequency{}, _surfaceAmplitude{}, _oreFrequency{}, _dirtDepth{}
{
	std::fstream configFile(std::string(worldConfigPath), std::ios::in);
	if (!configFile)
	{
		PRINT_ERROR_FILE("Failed to open file", worldConfigPath);
		return;
	}
	nlohmann::json configJson = nlohmann::json::parse(configFile);
	configFile.close();
	_chunkCountWidth = configJson["chunkCountWidth"].get<int>();
	_chunkCountHeight = configJson["chunkCountHeight"].get<int>();
	_chunkWidth = configJson["chunkWidth"].get<int>();
	_chunkHeight = configJson["chunkHeight"].get<int>();
	_surfaceFrequency = configJson["surfaceFrequency"].get<float>();
	_surfaceAmplitude = configJson["surfaceAmplitude"].get<float>();
	_oreFrequency = configJson["oreFrequency"].get<float>();
	_dirtDepth = configJson["dirtDepth"].get<int>();
	_structure = std::make_unique<SimpleCraft::Structure>(structureConfigPath);
	_ore = std::make_unique<SimpleCraft::Ore>(oreDataPath);
	_surfaceNoise.SetNoiseType(_surfaceNoise.NoiseType_Perlin);
	_oreNoise.SetNoiseType(_oreNoise.NoiseType_Cellular);
}
void SimpleCraft::World::GenerateChunk(const std::unordered_map<std::string, int>& tileDefinitions, glm::vec2 playerPosition)
{
	glm::ivec2 centerPosition = glm::ivec2(std::floor(playerPosition.x / _chunkWidth), std::floor(playerPosition.y / _chunkHeight));
	int leftEdge = centerPosition.x - _chunkCountWidth;
	int rightEdge = centerPosition.x + _chunkCountWidth;
	int bottomEdge = centerPosition.y - _chunkCountHeight;
	int topEdge = centerPosition.y + _chunkCountHeight;
	for (int y = bottomEdge; y <= topEdge; y++)
	{
		for (int x = leftEdge; x <= rightEdge; x++)
		{
			_chunks.try_emplace(MakeKey(x, y), _structure->GetStructures(), _surfaceNoise, _oreNoise, _ore->GetOreDefinitions(), tileDefinitions, _surfaceFrequency, _surfaceAmplitude, _oreFrequency, _dirtDepth, _chunkWidth, _chunkHeight, x, y);
		}
	}
}
void SimpleCraft::World::LoadChunk(glm::vec2 playerPosition)
{

}
void SimpleCraft::World::UnloadChunk(glm::vec2 playerPosition)
{
	glm::ivec2 centerPosition = glm::ivec2(std::floor(playerPosition.x / _chunkWidth), std::floor(playerPosition.y / _chunkHeight));
	int leftEdge = centerPosition.x - _chunkCountWidth;
	int rightEdge = centerPosition.x + _chunkCountWidth;
	int bottomEdge = centerPosition.y - _chunkCountHeight;
	int topEdge = centerPosition.y + _chunkCountHeight;
	for (std::unordered_map<int64_t, SimpleCraft::Chunk>::iterator it = _chunks.begin(); it != _chunks.end();)
	{
		int chunkX{};
		int chunkY{};
		SimpleCraft::World::DecodeKey(it->first, chunkX, chunkY);
		if (chunkX < leftEdge || chunkX > rightEdge || chunkY < bottomEdge || chunkY > topEdge)
		{
			it = _chunks.erase(it);
		}
		else
		{
			++it;
		}
	}
}
int SimpleCraft::World::GetTile(glm::vec2 worldPosition)
{
	int chunkX = (int)std::floor(worldPosition.x / _chunkWidth);
	int chunkY = (int)std::floor(worldPosition.y / _chunkHeight);
	if (std::unordered_map<int64_t, SimpleCraft::Chunk>::iterator it = _chunks.find(SimpleCraft::World::MakeKey(chunkX, chunkY)); it != _chunks.end())
	{
		return it->second.GetTile((int)std::floor(worldPosition.x) & (_chunkWidth - 1), (int)std::floor(worldPosition.y) & (_chunkHeight - 1));
	}
	return -1;
}
void SimpleCraft::World::SetTile(glm::vec2 worldPosition, int value)
{
	int chunkX = (int)std::floor(worldPosition.x / _chunkWidth);
	int chunkY = (int)std::floor(worldPosition.y / _chunkHeight);
	if (std::unordered_map<int64_t, SimpleCraft::Chunk>::iterator it = _chunks.find(SimpleCraft::World::MakeKey(chunkX, chunkY)); it != _chunks.end())
	{
		return it->second.SetTile((int)std::floor(worldPosition.x) & (_chunkWidth - 1), (int)std::floor(worldPosition.y) & (_chunkHeight - 1), value);
	}
}