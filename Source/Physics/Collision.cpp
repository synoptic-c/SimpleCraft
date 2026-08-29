#include"Collision.hpp"
const std::string* SimpleCraft::Collision::GetTileCollision(SimpleCraft::World& world, const SimpleCraft::Tile& tile, const glm::vec2& position)
{
	const std::string* tileName = tile.GetTileName(world.GetTile(position));
	if (!tileName)
	{
		return nullptr;
	}
	const std::string* tileCollision = tile.GetTileCollision(tileName);
	if (!tileCollision)
	{
		return nullptr;
	}
	return tileCollision;
}
bool SimpleCraft::Collision::TileResolveCollision(SimpleCraft::Bound bound, SimpleCraft::World& world, const SimpleCraft::Tile& tile, glm::vec2& position, glm::vec2 axisSpeed)
{
	if (glm::abs(axisSpeed.x) > float{})
	{
		const std::string* leftTop = GetTileCollision(world, tile, glm::vec2(position.x - bound.left, position.y + bound.top));
		const std::string* left = GetTileCollision(world, tile, glm::vec2(position.x - bound.left, position.y));
		const std::string* leftBottom = GetTileCollision(world, tile, glm::vec2(position.x - bound.left, position.y - bound.bottom));
		if (((leftTop && *leftTop == "solid") || (left && *left == "solid") || (leftBottom && *leftBottom == "solid")) && axisSpeed.x < float{})
		{
			position.x = std::floor(position.x) + bound.left;
			return true;
		}
		const std::string* rightTop = GetTileCollision(world, tile, glm::vec2(position.x + bound.right, position.y + bound.top));
		const std::string* right = GetTileCollision(world, tile, glm::vec2(position.x + bound.right, position.y));
		const std::string* rightBottom = GetTileCollision(world, tile, glm::vec2(position.x + bound.right, position.y - bound.bottom));
		if (((rightTop && *rightTop == "solid") || (right && *right == "solid") || (rightBottom && *rightBottom == "solid")) && axisSpeed.x > float{})
		{
			position.x = std::ceil(position.x) - bound.right - 0.001f;
			return true;
		}
	}
	if (glm::abs(axisSpeed.y) > float{})
	{
		const std::string* leftBottom = GetTileCollision(world, tile, glm::vec2(position.x - bound.left, position.y - bound.bottom));
		const std::string* bottom = GetTileCollision(world, tile, glm::vec2(position.x, position.y - bound.bottom));
		const std::string* rightBottom = GetTileCollision(world, tile, glm::vec2(position.x + bound.right, position.y - bound.bottom));
		if (((leftBottom && *leftBottom == "solid") || (bottom && *bottom == "solid") || (rightBottom && *rightBottom == "solid")) && axisSpeed.y < float{})
		{
			position.y = std::floor(position.y) + bound.bottom;
			return true;
		}
		const std::string* leftTop = GetTileCollision(world, tile, glm::vec2(position.x - bound.left, position.y + bound.top));
		const std::string* top = GetTileCollision(world, tile, glm::vec2(position.x, position.y + bound.top));
		const std::string* rightTop = GetTileCollision(world, tile, glm::vec2(position.x + bound.right, position.y + bound.top));
		if (((leftTop && *leftTop == "solid") || (top && *top == "solid") || (rightTop && *rightTop == "solid")) && axisSpeed.y > float{})
		{
			position.y = std::ceil(position.y) - bound.top - 0.001f;
			return true;
		}
	}
	return false;
}