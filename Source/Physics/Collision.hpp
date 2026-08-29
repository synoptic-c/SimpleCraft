#pragma once
#include<string>
#include<cmath>
#include<glm/glm.hpp>
#include"Bound.hpp"
#include"World/World.hpp"
#include"World/Tile.hpp"
namespace SimpleCraft
{
	class Collision
	{
	private:
		static const std::string* GetTileCollision(SimpleCraft::World& world, const SimpleCraft::Tile& tile, const glm::vec2& position);
	public:
		static bool TileResolveCollision(SimpleCraft::Bound bound, SimpleCraft::World& world, const SimpleCraft::Tile& tile, glm::vec2& position, glm::vec2 axisSpeed);
	};
}