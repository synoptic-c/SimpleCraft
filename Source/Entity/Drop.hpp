#pragma once
#include<vector>
#include<memory>
#include<string_view>
#include<string>
#include<nlohmann/json.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"Graphics/MeshManager.hpp"
#include"Graphics/ShaderManager.hpp"
#include"Graphics/Mesh.hpp"
#include"Graphics/Shader.hpp"
#include"Graphics/Camera.hpp"
#include"Physics/Bound.hpp"
#include"Physics/BoundManager.hpp"
#include"Physics/Overlap.hpp"
#include"Physics/Collision.hpp"
#include"Entity/Player.hpp"
#include"World/World.hpp"
#include"World/Tile.hpp"
#include"Container/Item.hpp"
#include"Util/Log.hpp"
namespace SimpleCraft
{
	class Drop
	{
	private:
		std::vector<glm::vec2> _positions;
		std::vector<glm::vec2> _speeds;
		std::vector<std::string> _names;
		glm::vec2 _scale;
		float _gravity;
	public:
		Drop(std::string_view path);
		void Update(const SimpleCraft::BoundManager& boundManager, SimpleCraft::World& world, const SimpleCraft::Tile& tile, const SimpleCraft::Player& player, SimpleCraft::Item& item, float deltaTime);
		void Render(const SimpleCraft::MeshManager& meshManager, SimpleCraft::ShaderManager& shaderManager, SimpleCraft::Tile& tile, const SimpleCraft::Camera& camera);
		void Add(glm::vec2 position, const std::string& name);
		void Add(glm::vec2 position, const std::string* name);
		void Delete(unsigned int index);
	};
}