#pragma once
#include<string>
#include<string_view>
#include<unordered_map>
#include<fstream>
#include<nlohmann/json.hpp>
#include"Graphics/Mesh.hpp"
#include"Util/Log.hpp"
namespace SimpleCraft
{
	class MeshManager
	{
	private:
		std::unordered_map<std::string, SimpleCraft::Mesh> _meshes;
	public:
		MeshManager(std::string_view configPath);
		const SimpleCraft::Mesh* GetMesh(std::string_view name) const;
	};
}