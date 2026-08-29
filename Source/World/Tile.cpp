#include"Tile.hpp"
SimpleCraft::Tile::Tile(std::string_view configPath, std::string_view dataPath) : _tileWidth{}, _tileHeight{}, _widthCount{}, _heightCount{}
{
	std::fstream configFile(std::string(configPath), std::ios::in);
	if (!configFile)
	{
		PRINT_ERROR_FILE("Failed to open file", configPath);
		return;
	}
	nlohmann::json configJson = nlohmann::json::parse(configFile);
	configFile.close();
	_tileWidth = configJson["tileWidth"].get<float>();
	_tileHeight = configJson["tileHeight"].get<float>();
	_widthCount = configJson["widthCount"].get<unsigned int>();
	_heightCount = configJson["heightCount"].get<unsigned int>();
	std::fstream dataFile(std::string(dataPath), std::ios::in);
	if (!dataFile)
	{
		PRINT_ERROR_FILE("Failed to open file", dataPath);
		return;
	}
	nlohmann::json dataJson = nlohmann::json::parse(dataFile);
	dataFile.close();
	std::vector<std::string> names = dataJson["names"].get<std::vector<std::string>>();
	std::string texturePath = configJson["texturePath"].get<std::string>();
	std::string textureExtension = configJson["textureExtension"].get<std::string>();
	for (int i = 0;i < (int)names.size();i++)
	{
		_textures.emplace_back(texturePath + names[i] + textureExtension);
		_tileDefinitions.insert({ names[i], i });
	}
	for (const nlohmann::json& json : dataJson["fixedTiles"])
	{
		_tileDefinitions.insert({ json["name"].get<std::string>(), json["index"].get<int>()});
	}
	for (std::unordered_map<std::string, int>::const_iterator it = _tileDefinitions.begin(); it != _tileDefinitions.end(); ++it)
	{
		_tileNames.insert({ it->second, it->first });
	}
	for (const nlohmann::json& json : dataJson["collisions"])
	{
		_tileCollisions.insert({ json["name"].get<std::string>(), json["collision"].get<std::string>() });
	}
}
void SimpleCraft::Tile::Render(const SimpleCraft::MeshManager& meshManager, SimpleCraft::ShaderManager& shaderManager, const SimpleCraft::Camera& camera, SimpleCraft::World& world)
{
	const SimpleCraft::Mesh* mesh = meshManager.GetMesh("quad");
	SimpleCraft::Shader* shader = shaderManager.GetShader("basic");
	if (!mesh || !shader || !_textures.size())
	{
		return;
	}
	mesh->Bind();
	shader->Use();
	shader->SetMat4("u_projection", camera.GetProjection());
	shader->SetMat4("u_view", glm::mat4(1.0f));
	glm::vec2 position{};
	glm::vec2 index{};
	position.y = std::fmod(-camera.GetView().y, _tileHeight) - _tileHeight;
	index.y = (int)camera.GetView().y - std::floor((camera.GetReferenceTop() + camera.GetReferenceBottom()) * 0.5f) - _tileHeight * 2.0f;
	float bottomEdge = position.y + camera.GetBottom() - _tileHeight;
	float topEdge =	position.y + camera.GetTop() + _tileHeight * 1.5f;
	for (unsigned int y = 0; y < _heightCount; y++)
	{
		position.x = std::fmod(-camera.GetView().x, _tileWidth) - _tileWidth * 0.5f;
		float leftEdge = position.x + camera.GetLeft() - _tileWidth;
		float rightEdge = position.x + camera.GetRight() + _tileWidth * 2.0f;
		index.x = (int)camera.GetView().x - std::floor((camera.GetReferenceRight() + camera.GetReferenceLeft()) * 0.5f) - _tileWidth * 0.5f;
		for (unsigned int x = 0; x < _widthCount; x++)
		{
			if (position.x > leftEdge && position.x < rightEdge && position.y > bottomEdge && position.y < topEdge)
			{
				int type = world.GetTile(index);
				if (type > GetTileDefinition("air"))
				{
					shader->SetMat4("u_model", glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f)));
					_textures[type].Bind(unsigned int{});
					mesh->Draw();
				}
			}
			position.x += _tileWidth;
			index.x++;
		}
		position.y += _tileHeight;
		index.y++;
	}
}
const std::vector<SimpleCraft::Texture>& SimpleCraft::Tile::GetTextures() const
{
	return _textures;
}
const std::unordered_map<std::string, int>& SimpleCraft::Tile::GetTileDefinitions() const
{
	return _tileDefinitions;
}
const std::unordered_map<int, std::string>& SimpleCraft::Tile::GetTileNames() const
{
	return _tileNames;
}
const std::unordered_map<std::string, std::string>& SimpleCraft::Tile::GetTileCollisions() const
{
	return _tileCollisions;
}
int SimpleCraft::Tile::GetTileDefinition(std::string_view name) const
{
	if (std::unordered_map<std::string, int>::const_iterator it = _tileDefinitions.find(std::string(name)); it != _tileDefinitions.end())
	{
		return it->second;
	}
	return -1;
}
const std::string* SimpleCraft::Tile::GetTileName(int name) const
{
	if (std::unordered_map<int, std::string>::const_iterator it = _tileNames.find(name); it != _tileNames.end())
	{
		return &it->second;
	}
	return nullptr;
}
const std::string* SimpleCraft::Tile::GetTileCollision(std::string_view name) const
{
	if (std::unordered_map<std::string, std::string>::const_iterator it = _tileCollisions.find(std::string(name)); it != _tileCollisions.end())
	{
		return &it->second;
	}
	return nullptr;
}
const std::string* SimpleCraft::Tile::GetTileCollision(const std::string* name) const
{
	if (std::unordered_map<std::string, std::string>::const_iterator it = _tileCollisions.find(*name); it != _tileCollisions.end())
	{
		return &it->second;
	}
	return nullptr;
}
float SimpleCraft::Tile::GetTileWidth() const
{
	return _tileWidth;
}
float SimpleCraft::Tile::GetTileHeight() const
{
	return _tileHeight;
}