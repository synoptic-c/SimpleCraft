#pragma once
#include<memory>
#include<string>
#include<string_view>
#include<fstream>
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
#include"Util/Log.hpp"
namespace SimpleCraft
{
	class Inventory
	{
	private:
		std::unique_ptr<SimpleCraft::Texture> _texture;
		std::unique_ptr<SimpleCraft::Atlas> _atlas;
		glm::vec2 _scale;
	public:
		Inventory(std::string_view path);
		void Render(bool isInventory, const SimpleCraft::MeshManager& meshManager, SimpleCraft::ShaderManager& shaderManager, const SimpleCraft::Camera& camera);
	};
}