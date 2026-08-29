#include"Chunk.hpp"
int SimpleCraft::Chunk::GetTileDefinition(const std::unordered_map<std::string, int>& tileDefinitions, std::string_view name)
{
	if (std::unordered_map<std::string, int>::const_iterator it = tileDefinitions.find(std::string(name)); it != tileDefinitions.end())
	{
		return it->second;
	}
	return -1;
}
const SimpleCraft::StructureData* SimpleCraft::Chunk::GetStructureData(const std::unordered_map<std::string, SimpleCraft::StructureData>& structures, std::string_view name)
{
	if (std::unordered_map<std::string, SimpleCraft::StructureData>::const_iterator it = structures.find(std::string(name)); it != structures.end())
	{
		return &it->second;
	}
	return nullptr;
}
SimpleCraft::Chunk::Chunk(const std::unordered_map<std::string, SimpleCraft::StructureData>& structures, const FastNoiseLite& surfaceNoise, const FastNoiseLite& oreNoise, const std::vector<SimpleCraft::OreDefinition>& oreDefinitions, const std::unordered_map<std::string, int>& tileDefinitions, float surfaceFrequency, float surfaceAmplitude, float oreFrequency, int dirtDepth, int width, int height, int chunkX, int chunkY) : _width(width), _height(height), _data{}
{
	_data.reserve(_width * _height);
	for (int y = 0; y < _height; y++)
	{
		int worldY = chunkY * _height + y;
		for (int x = 0; x < _width; x++)
		{
			int worldX = chunkX * _width + x;
			int surfaceY = GetSurfaceY(surfaceNoise, worldX, surfaceFrequency, surfaceAmplitude);
			float oreValue = oreNoise.GetNoise((float)worldX * oreFrequency, (float)worldY * oreFrequency);
			if (worldY > surfaceY)
			{
				_data.emplace_back(GetTileDefinition(tileDefinitions, "air"));
			}
			else if (worldY == surfaceY)
			{
				_data.emplace_back(GetTileDefinition(tileDefinitions, "grass_side"));
			}
			else if (worldY > surfaceY - dirtDepth)
			{
				_data.emplace_back(GetTileDefinition(tileDefinitions, "dirt"));
			}
			else if (worldY < surfaceY - (dirtDepth - 1))
			{
				int tile = GetTileDefinition(tileDefinitions, "stone");
				for (int i = 0; i < oreDefinitions.size();i++)
				{
					if (oreValue < oreDefinitions[i].threshold && worldY < surfaceY - oreDefinitions[i].depth)
					{
						tile = GetTileDefinition(tileDefinitions, oreDefinitions[i].name);
						break;
					}
				}
				_data.emplace_back(tile);
			}
		}
	}
	//const SimpleCraft::StructureData* structureTree = GetStructureData(structures, "tree");
	//for (int y = 0; y < _height; y++)
	//{
	//	int worldY = chunkY * _height + y;
	//	for (int x = 0; x < _width; x++)
	//	{
	//		int worldX = chunkX * _width + x;
	//		int surfaceY = GetSurfaceY(surfaceNoise, worldX, surfaceFrequency, surfaceAmplitude);
	//		StructurePlace(structureTree, tileDefinitions, chunkX, chunkY);
	//	}
	//}
}
int SimpleCraft::Chunk::GetSurfaceY(const FastNoiseLite& surfaceNoise, int worldX, float surfaceFrequency, float surfaceAmplitude)
{
	float surfaceValue = surfaceNoise.GetNoise((float)worldX * surfaceFrequency, float{});
	int surfaceY = (int)(surfaceValue * surfaceAmplitude);
	return surfaceY;
}
void SimpleCraft::Chunk::StructurePlace(const SimpleCraft::StructureData* structureData, const std::unordered_map<std::string, int>& tileDefinitions, int chunkX, int chunkY)
{
	for (int y = 0; y < structureData->height; y++)
	{
		for (int x = 0; x < structureData->width; x++)
		{
			if (x < _width && y < _height)
			{
				unsigned int index = x + (structureData->height - y - 1) * structureData->width;
				if (index < structureData->tiles.size())
				{
					_data[x + y * _width] = GetTileDefinition(tileDefinitions, structureData->tiles[index]);
				}
			}
		}
	}
}
int SimpleCraft::Chunk::GetTile(int localX, int localY) const
{
	if (localX >= 0 && localX < _width && localY >= 0 && localY < _height)
	{
		return _data[localX + localY * _width];
	}
	return -1;
}
void SimpleCraft::Chunk::SetTile(int localX, int localY, int value)
{
	if (localX >= 0 && localX < _width && localY >= 0 && localY < _height)
	{
		_data[localX + localY * _width] = value;
	}
}