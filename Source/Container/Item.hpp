#pragma once
#include<vector>
#include<unordered_map>
#include<string>
#include<string_view>
#include<fstream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<nlohmann/json.hpp>
#include"Graphics/Mesh.hpp"
#include"Graphics/Shader.hpp"
#include"Graphics/Font.hpp"
#include"Graphics/MeshManager.hpp"
#include"Graphics/ShaderManager.hpp"
#include"Graphics/FontManager.hpp"
#include"Graphics/FontRender.hpp"
#include"Graphics/Camera.hpp"
#include"World/Tile.hpp"
#include"Util/Input.hpp"
#include"Util/Log.hpp"
namespace SimpleCraft
{
	struct ItemContent
	{
		std::string name;
		unsigned int count;
	};
	struct ItemGrid
	{
		glm::vec2 start;
		glm::vec2 size;
	};
	class Item
	{
	private:
		std::vector<std::string> _names;
		std::unordered_map<std::string, std::vector<SimpleCraft::ItemContent>> _items;
		std::unordered_map<std::string, unsigned int> _widthCounts;
		std::unordered_map<std::string, unsigned int> _heightCounts;
		std::unordered_map<std::string, glm::vec2> _offsets;
		std::unordered_map<std::string, glm::vec2> _spaces;
		std::unordered_map<std::string, SimpleCraft::ItemGrid> _itemGrids;
		glm::vec2 _fontOffset;
		glm::vec2 _fontScale;
		glm::vec2 _scale;
		unsigned int _stackCount;
		unsigned int _chooseSlot;
		SimpleCraft::ItemContent _selectItem;
		unsigned int _limit;
	public:
		Item(std::string_view path);
		void Update(const SimpleCraft::Camera& camera, SimpleCraft::Input& input);
		void Render(bool isInventory, const SimpleCraft::MeshManager& meshManager, SimpleCraft::ShaderManager& shaderManager, const SimpleCraft::FontManager& fontManager, const SimpleCraft::Tile& tile, const SimpleCraft::Input& input, const SimpleCraft::Camera& camera);
		void RenderItem(const SimpleCraft::Mesh* mesh, SimpleCraft::Shader* shader, const SimpleCraft::Tile& tile);
		void RenderSelectItem(const SimpleCraft::Mesh* mesh, SimpleCraft::Shader* shader, const SimpleCraft::Tile& tile, const SimpleCraft::Input& input, const SimpleCraft::Camera& camera);
		void RenderFont(const SimpleCraft::Mesh* mesh, SimpleCraft::Shader* shader, const SimpleCraft::Font* font);
		void RenderSelectFont(const SimpleCraft::Mesh* mesh, SimpleCraft::Shader* shader, const SimpleCraft::Font* font, const SimpleCraft::Camera& camera, const SimpleCraft::Input& input);
		glm::vec2 GetSlotPosition(glm::uvec2 position, glm::vec2 offset, glm::vec2 space);
		std::vector<SimpleCraft::ItemContent>* GetItemList(std::string_view name);
		const std::vector<SimpleCraft::ItemContent>* GetItemList(std::string_view name) const;
		const SimpleCraft::ItemContent* GetItemPointer(std::string_view name, unsigned int x, unsigned int y) const;
		SimpleCraft::ItemContent* GetItemPointer(std::string_view name, unsigned int x, unsigned int y);
		SimpleCraft::ItemContent GetItem(std::string_view name, unsigned int x, unsigned int y) const;
		SimpleCraft::ItemContent GetItem(std::string_view name, unsigned int x, unsigned int y, unsigned int limit);
		void SetItem(std::string_view name, unsigned int x, unsigned int y, const SimpleCraft::ItemContent& value);
		void SetItem(std::string_view name, unsigned int x, unsigned int y, SimpleCraft::ItemContent& value, unsigned int limit);
		bool AddItem(const std::vector<std::string_view>& names, std::string_view value);
		void AddItems(const std::vector<std::string_view>& names, SimpleCraft::ItemContent& value);
		void StackItems(std::string_view name, unsigned int x, unsigned int y, SimpleCraft::ItemContent& value, unsigned int limit = 0);
		void StackItems(SimpleCraft::ItemContent& valueSelf, SimpleCraft::ItemContent& valueOther, unsigned int limit = 0);
		void StackItems(SimpleCraft::ItemContent* valueSelf, SimpleCraft::ItemContent& valueOther, unsigned int limit = 0);
		std::string DeleteItem(std::string_view name);
		unsigned int GetWidthCount(std::string_view name) const;
		unsigned int GetHeightCount(std::string_view name) const;
		glm::vec2 GetOffset(std::string_view name) const;
		glm::vec2 GetSpace(std::string_view name) const;
		SimpleCraft::ItemGrid GetItemGrid(std::string_view name) const;
	};
}