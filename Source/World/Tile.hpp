#pragma once
#include<memory>
#include<vector>
#include<unordered_map>
#include<string>
#include<string_view>
#include<fstream>
#include<cmath>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<nlohmann/json.hpp>
#include"Util/Log.hpp"
#include"Graphics/Mesh.hpp"
#include"Graphics/Shader.hpp"
#include"Graphics/MeshManager.hpp"
#include"Graphics/ShaderManager.hpp"
#include"Graphics/Texture.hpp"
#include"Graphics/Camera.hpp"
#include"World/World.hpp"
namespace SimpleCraft
{
	class Tile
	{
	private:
		std::vector<SimpleCraft::Texture> _textures;
		std::unordered_map<std::string, int> _tileDefinitions;
		std::unordered_map<int, std::string> _tileNames;
		std::unordered_map<std::string, std::string> _tileCollisions;
		float _tileWidth;
		float _tileHeight;
		unsigned int _widthCount;
		unsigned int _heightCount;
	public:
		Tile(std::string_view configPath, std::string_view dataPath);
		void Render(const SimpleCraft::MeshManager& meshManager, SimpleCraft::ShaderManager& shaderManager, const SimpleCraft::Camera& camera, SimpleCraft::World& world);
		const std::vector<SimpleCraft::Texture>& GetTextures() const;
		const std::unordered_map<std::string, int>& GetTileDefinitions() const;
		const std::unordered_map<int, std::string>& GetTileNames() const;
		const std::unordered_map<std::string, std::string>& GetTileCollisions() const;
		int GetTileDefinition(std::string_view name) const;
		const std::string* GetTileName(int name) const;
		const std::string* GetTileCollision(std::string_view name) const;
		const std::string* GetTileCollision(const std::string* name) const;
		float GetTileWidth() const;
		float GetTileHeight() const;
	};
}