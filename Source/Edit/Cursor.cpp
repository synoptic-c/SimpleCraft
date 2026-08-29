#include"Cursor.hpp"
void SimpleCraft::Cursor::Update(SimpleCraft::Drop& drop, SimpleCraft::World& world, const SimpleCraft::Tile& tile, SimpleCraft::Item& item, const SimpleCraft::Camera& camera, const SimpleCraft::Input& input)
{
	if (input.GetIsInventory())
	{
		return;
	}
	glm::vec2 mousePosition(
		camera.GetView().x + input.GetMouseWorld().x - (camera.GetRight() - camera.GetLeft()) * 0.5f,
		camera.GetView().y + input.GetMouseWorld().y - (camera.GetTop() - camera.GetBottom()) * 0.5f
	);
	AttcakDestroy(drop, world, tile, input, mousePosition);
	UsePlace(drop, world, tile, item, input, mousePosition);
}
void SimpleCraft::Cursor::AttcakDestroy(SimpleCraft::Drop& drop, SimpleCraft::World& world, const SimpleCraft::Tile& tile, const SimpleCraft::Input& input, glm::vec2 mousePosition)
{
	if (!input.GetAttackDestroy())
	{
		return;
	}
	const std::string* tileName = tile.GetTileName(world.GetTile(mousePosition));
	if (!tileName || *tileName == "air")
	{
		return;
	}
	world.SetTile(
		mousePosition,
		tile.GetTileDefinition("air")
	);
	drop.Add(
		glm::vec2(
			std::floor(mousePosition.x) + tile.GetTileWidth() * 0.5f,
			std::floor(mousePosition.y) + tile.GetTileHeight() * 0.5f
		),
		tileName
	);
}
void SimpleCraft::Cursor::UsePlace(SimpleCraft::Drop& drop, SimpleCraft::World& world, const SimpleCraft::Tile& tile, SimpleCraft::Item& item, const SimpleCraft::Input& input, glm::vec2 mousePosition)
{
	if (!input.GetUsePlace())
	{
		return;
	}
	const std::string* center = tile.GetTileName(world.GetTile(mousePosition));
	const std::string* left = tile.GetTileName(world.GetTile(glm::vec2(mousePosition.x - tile.GetTileWidth(), mousePosition.y)));
	const std::string* right = tile.GetTileName(world.GetTile(glm::vec2(mousePosition.x + tile.GetTileWidth(), mousePosition.y)));
	const std::string* bottom = tile.GetTileName(world.GetTile(glm::vec2(mousePosition.x, mousePosition.y - tile.GetTileHeight())));
	const std::string* top = tile.GetTileName(world.GetTile(glm::vec2(mousePosition.x, mousePosition.y + tile.GetTileHeight())));
	if ((!center || !left || !right || !bottom || !top) || (*left == "air" && *right == "air" && *bottom == "air" && *top == "air"))
	{
		return;
	}
	if (*center == "air")
	{
		std::string itemName = item.DeleteItem("quickSlotItems");
		if (itemName == "air")
		{
			return;
		}
		world.SetTile(
			mousePosition,
			tile.GetTileDefinition(itemName)
		);
	}
}