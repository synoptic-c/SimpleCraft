#pragma once
#include<cmath>
#include<string>
#include<glm/glm.hpp>
#include"World/World.hpp"
#include"World/Tile.hpp"
#include"Entity/Drop.hpp"
#include"Container/Item.hpp"
#include"Graphics/Camera.hpp"
#include"Util/Input.hpp"
namespace SimpleCraft
{
	class Cursor
	{
	private:

	public:
		void Update(SimpleCraft::Drop& drop, SimpleCraft::World& world, const SimpleCraft::Tile& tile, SimpleCraft::Item& item, const SimpleCraft::Camera& camera, const SimpleCraft::Input& input);
		void AttcakDestroy(SimpleCraft::Drop& drop, SimpleCraft::World& world, const SimpleCraft::Tile& tile, const SimpleCraft::Input& input, glm::vec2 mousePosition);
		void UsePlace(SimpleCraft::Drop& drop, SimpleCraft::World& world, const SimpleCraft::Tile& tile, SimpleCraft::Item& item, const SimpleCraft::Input& input, glm::vec2 mousePosition);
	};
}