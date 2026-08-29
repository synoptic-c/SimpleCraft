#pragma once
#include<memory>
#include<fstream>
#include<string>
#include<string_view>
#include<unordered_map>
#include<nlohmann/json.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"Graphics/Mesh.hpp"
#include"Graphics/Shader.hpp"
#include"Graphics/MeshManager.hpp"
#include"Graphics/ShaderManager.hpp"
#include"Graphics/Texture.hpp"
#include"Graphics/Camera.hpp"
#include"Graphics/Atlas.hpp"
#include"Graphics/Animation.hpp"
#include"Physics/BoundManager.hpp"
#include"Physics/Collision.hpp"
#include"Physics/Bound.hpp"
#include"Util/Log.hpp"
#include"World/World.hpp"
#include"World/Tile.hpp"
#include"Util/Input.hpp"
namespace SimpleCraft
{
	class Player
	{
	private:
		std::unique_ptr<SimpleCraft::Texture> _texture;
		std::unique_ptr<SimpleCraft::Atlas> _atlas;
		std::unique_ptr<SimpleCraft::Animation> _animation;
		glm::vec2 _position;
		glm::vec2 _speed;
		float _direction;
		float _walkSpeed;
		float _gravity;
		float _falling;
		float _hangTime;
		float _jumpSpeed;
	public:
		Player(std::string_view configPath);
		void Update(const SimpleCraft::BoundManager& boundManager, SimpleCraft::World& world, const SimpleCraft::Tile& tile, const SimpleCraft::Input& input, float deltaTime);
		void Render(const SimpleCraft::MeshManager& meshManager, SimpleCraft::ShaderManager& shaderManager, const SimpleCraft::Camera& camera, float deltaTime);
		glm::vec2 GetPosition() const;
	};
}