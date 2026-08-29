#include"Item.hpp"
SimpleCraft::Item::Item(std::string_view path) : _scale{}, _stackCount{}, _fontOffset{}, _fontScale{}, _chooseSlot{}, _selectItem{}, _limit{}
{
	//inventory pixel
	//scale x 176
	//scale y 166
	//position
	//example
	//left edge
	//(camera right - camera left) / 2.0 - inventory size x / 2.0
	//(16.0 - 0.0) / 2.0 - 4.0 / 2.0
	//6
	//any x
	//left edge + any pixel x / scale x * model scale x
	//6 + 16 / 176 * 4.0
	//6.3636363
	std::fstream file(std::string(path), std::ios::in);
	if (!file)
	{
		PRINT_ERROR_FILE("Failed to open file", path);
		return;
	}
	nlohmann::json json = nlohmann::json::parse(file);
	file.close();
	_scale = glm::vec2(json["scale"]["x"].get<float>(), json["scale"]["y"].get<float>());
	_fontOffset = glm::vec2(json["fontOffset"]["x"].get<float>(), json["fontOffset"]["y"].get<float>());
	_fontScale = glm::vec2(json["fontScale"]["x"].get<float>(), json["fontScale"]["y"].get<float>());
	_stackCount = json["stackCount"].get<unsigned char>();
	_names = json["names"].get<std::vector<std::string>>();
	_limit = json["limit"].get<unsigned int>();
	_selectItem = SimpleCraft::ItemContent{ "air", 0 };
	std::vector<unsigned int> widthCounts = json["widthCounts"].get<std::vector<unsigned int>>();
	std::vector<unsigned int> heightCounts = json["heightCounts"].get<std::vector<unsigned int>>();
	for (unsigned int i = 0; i < _names.size(); i++)
	{
		_widthCounts.emplace(_names[i], widthCounts[i]);
		_heightCounts.emplace(_names[i], heightCounts[i]);
		_offsets.emplace(std::piecewise_construct, std::forward_as_tuple(_names[i]), std::forward_as_tuple(glm::vec2(json["offsets"][i]["x"].get<float>(), json["offsets"][i]["y"].get<float>())));
		_spaces.emplace(std::piecewise_construct, std::forward_as_tuple(_names[i]), std::forward_as_tuple(glm::vec2(json["spaces"][i]["x"].get<float>(), json["spaces"][i]["y"].get<float>())));
		_itemGrids.emplace(std::piecewise_construct, std::forward_as_tuple(_names[i]), std::forward_as_tuple(SimpleCraft::ItemGrid{ glm::vec2(json["grid"][i]["start"]["x"].get<float>(), json["grid"][i]["start"]["y"].get<float>()), glm::vec2(json["grid"][i]["size"]["x"].get<float>(), json["grid"][i]["size"]["y"].get<float>()) }));
		_items.emplace(_names[i], std::vector<SimpleCraft::ItemContent>{});
		std::vector<SimpleCraft::ItemContent>* item = GetItemList(_names[i]);
		unsigned int itemSize = GetWidthCount(_names[i]) * GetHeightCount(_names[i]);
		item->reserve(itemSize);
		for (unsigned int j = 0; j < itemSize; j++)
		{
			item->emplace_back(SimpleCraft::ItemContent{ "air", 0 });
		}
	}
}
void SimpleCraft::Item::Update(const SimpleCraft::Camera& camera, SimpleCraft::Input& input)
{
	const std::vector<unsigned char>& slots = input.GetSlots();
	for (unsigned int i = 0; i < slots.size(); i++)
	{
		if (slots[i])
		{
			_chooseSlot = i;
			break;
		}
	}
	if (input.GetIsInventory())
	{
		for (unsigned int i = 0; i < _names.size(); i++)
		{
			if (input.GetClickLeft())
			{
				const std::string& name = _names[i];
				SimpleCraft::ItemGrid itemGrid = GetItemGrid(name);
				glm::vec2 mousePosition = input.GetMouseWorld();
				mousePosition += glm::vec2(camera.GetLeft(), camera.GetBottom());
				if (mousePosition.y > itemGrid.start.y)
				{
					glm::uvec2 position = glm::floor((mousePosition - itemGrid.start) / itemGrid.size);
					SimpleCraft::ItemContent* selectItem = GetItemPointer(name, position.x, position.y);
					if (selectItem && _selectItem.name == "air" && selectItem->name != "air")
					{
						_selectItem = *selectItem;
						SetItem(name, position.x, position.y, SimpleCraft::ItemContent{ "air", 0 });
						break;
					}
					if (selectItem && _selectItem.name != "air" && selectItem->name == "air")
					{
						SetItem(name, position.x, position.y, _selectItem);
						_selectItem = SimpleCraft::ItemContent{ "air", 0 };
						break;
					}
					if (selectItem && _selectItem.name == selectItem->name)
					{
						StackItems(selectItem, _selectItem);
						break;
					}
				}
			}
			if (input.GetClickRight())
			{
				const std::string& name = _names[i];
				SimpleCraft::ItemGrid itemGrid = GetItemGrid(name);
				glm::vec2 mousePosition = input.GetMouseWorld();
				mousePosition += glm::vec2(camera.GetLeft(), camera.GetBottom());
				if (mousePosition.y > itemGrid.start.y)
				{
					glm::uvec2 position = glm::floor((mousePosition - itemGrid.start) / itemGrid.size);
					SimpleCraft::ItemContent* selectItem = GetItemPointer(name, position.x, position.y);
					if (selectItem && _selectItem.name != "air" && selectItem->name == "air")
					{
						SetItem(name, position.x, position.y, _selectItem, _limit);
						break;
					}
					if (selectItem && _selectItem.name == "air" && selectItem->name != "air")
					{
						_selectItem = GetItem(name, position.x, position.y, _limit);
						break;
					}
					if (selectItem && _selectItem.name == selectItem->name)
					{
						StackItems(selectItem, _selectItem, _limit);
						break;
					}
				}
			}
		}
	}
}
void SimpleCraft::Item::Render(bool isInventory, const SimpleCraft::MeshManager& meshManager, SimpleCraft::ShaderManager& shaderManager, const SimpleCraft::FontManager& fontManager, const SimpleCraft::Tile& tile, const SimpleCraft::Input& input, const SimpleCraft::Camera& camera)
{
	if (!isInventory)
	{
		return;
	}
	const SimpleCraft::Mesh* mesh = meshManager.GetMesh("quad");
	SimpleCraft::Shader* shader = shaderManager.GetShader("basic");
	if (!mesh || !shader || !tile.GetTextures().size())
	{
		return;
	}
	mesh->Bind();
	shader->Use();
	shader->SetMat4("u_projection", camera.GetProjection());
	shader->SetMat4("u_view", glm::mat4(1.0f));
	RenderItem(mesh, shader, tile);
	RenderSelectItem(mesh, shader, tile, input, camera);
	shader = shaderManager.GetShader("font");
	const SimpleCraft::Font* font = fontManager.GetFont("notoSans");
	if (!shader || !font)
	{
		return;
	}
	shader->Use();
	shader->SetMat4("u_projection", camera.GetProjection());
	shader->SetMat4("u_view", glm::mat4(1.0f));
	RenderFont(mesh, shader, font);
	RenderSelectFont(mesh, shader, font, camera, input);
}
void SimpleCraft::Item::RenderItem(const SimpleCraft::Mesh* mesh, SimpleCraft::Shader* shader, const SimpleCraft::Tile& tile)
{
	for (unsigned int i = 0; i < _names.size(); i++)
	{
		for (unsigned int y = 0; y < GetHeightCount(_names[i]); y++)
		{
			for (unsigned int x = 0; x < GetWidthCount(_names[i]); x++)
			{
				glm::mat4 model = glm::mat4(1.0f);
				const std::string& name = _names[i];
				glm::vec2 position = GetSlotPosition(glm::uvec2(x, y), GetOffset(name), GetSpace(name));
				model = glm::translate(model, glm::vec3(position, float{}));
				model = glm::scale(model, glm::vec3(_scale, float{}));
				shader->SetMat4("u_model", model);
				const SimpleCraft::ItemContent* itemContent = GetItemPointer(name, x, y);
				if (itemContent && itemContent->name != "air")
				{
					tile.GetTextures()[tile.GetTileDefinition(itemContent->name)].Bind(unsigned int{});
					mesh->Draw();
				}
			}
		}
	}
}
void SimpleCraft::Item::RenderSelectItem(const SimpleCraft::Mesh* mesh, SimpleCraft::Shader* shader, const SimpleCraft::Tile& tile, const SimpleCraft::Input& input, const SimpleCraft::Camera& camera)
{
	if (_selectItem.name == "air")
	{
		return;
	}
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec2 position = input.GetMouseWorld();
	model = glm::translate(model, glm::vec3(position, float{}));
	model = glm::translate(model, glm::vec3(camera.GetLeft(), camera.GetBottom(), float{}));
	model = glm::scale(model, glm::vec3(_scale, float{}));
	shader->SetMat4("u_model", model);
	tile.GetTextures()[tile.GetTileDefinition(_selectItem.name)].Bind(unsigned int{});
	mesh->Draw();
}
void SimpleCraft::Item::RenderFont(const SimpleCraft::Mesh* mesh, SimpleCraft::Shader* shader, const SimpleCraft::Font* font)
{
	for (unsigned int i = 0; i < _names.size(); i++)
	{
		for (unsigned int y = 0; y < GetHeightCount(_names[i]); y++)
		{
			for (unsigned int x = 0; x < GetWidthCount(_names[i]); x++)
			{
				const std::string& name = _names[i];
				glm::vec2 position = GetSlotPosition(glm::uvec2(x, y), GetOffset(name) + _fontOffset, GetSpace(name));
				const SimpleCraft::ItemContent* itemContent = GetItemPointer(name, x, y);
				if (itemContent && itemContent->count > 1)
				{
					SimpleCraft::FontRender::RenderText(mesh, shader, font, std::to_string(itemContent->count), position, _fontScale);
				}
			}
		}
	}
}
void SimpleCraft::Item::RenderSelectFont(const SimpleCraft::Mesh* mesh, SimpleCraft::Shader* shader, const SimpleCraft::Font* font, const SimpleCraft::Camera& camera, const SimpleCraft::Input& input)
{
	if (_selectItem.name == "air")
	{
		return;
	}
	glm::vec2 position = input.GetMouseWorld() + _fontOffset + glm::vec2(camera.GetLeft(), camera.GetBottom());
	unsigned int count = _selectItem.count;
	if (count > 1)
	{
		SimpleCraft::FontRender::RenderText(mesh, shader, font, std::to_string(count), position, _fontScale);
	}
}
glm::vec2 SimpleCraft::Item::GetSlotPosition(glm::uvec2 position, glm::vec2 offset, glm::vec2 space)
{
	return offset + (glm::vec2)position * space;
}
std::vector<SimpleCraft::ItemContent>* SimpleCraft::Item::GetItemList(std::string_view name)
{
	if (std::unordered_map<std::string, std::vector<SimpleCraft::ItemContent>>::iterator it = _items.find(std::string(name)); it != _items.end())
	{
		return &it->second;
	}
	return nullptr;
}
const std::vector<SimpleCraft::ItemContent>* SimpleCraft::Item::GetItemList(std::string_view name) const
{
	if (std::unordered_map<std::string, std::vector<SimpleCraft::ItemContent>>::const_iterator it = _items.find(std::string(name)); it != _items.end())
	{
		return &it->second;
	}
	return nullptr;
}
const SimpleCraft::ItemContent* SimpleCraft::Item::GetItemPointer(std::string_view name, unsigned int x, unsigned int y) const
{
	unsigned int widthCount = GetWidthCount(name);
	const std::vector<SimpleCraft::ItemContent>* item = GetItemList(name);
	if (!item)
	{
		return nullptr;
	}
	if (x >= 0 && x < widthCount && y >= 0 && y < GetHeightCount(name))
	{
		return &(*item)[x + y * widthCount];
	}
	return nullptr;
}
SimpleCraft::ItemContent SimpleCraft::Item::GetItem(std::string_view name, unsigned int x, unsigned int y) const
{
	unsigned int widthCount = GetWidthCount(name);
	const std::vector<SimpleCraft::ItemContent>* item = GetItemList(name);
	if (!item)
	{
		return SimpleCraft::ItemContent{ "air",0 };
	}
	if (x >= 0 && x < widthCount && y >= 0 && y < GetHeightCount(name))
	{
		return (*item)[x + y * widthCount];
	}
	return SimpleCraft::ItemContent{ "air", 0 };
}
SimpleCraft::ItemContent SimpleCraft::Item::GetItem(std::string_view name, unsigned int x, unsigned int y, unsigned int limit)
{
	unsigned int widthCount = GetWidthCount(name);
	std::vector<SimpleCraft::ItemContent>* item = GetItemList(name);
	if (!item)
	{
		return SimpleCraft::ItemContent{ "air",0 };
	}
	if (x >= 0 && x < widthCount && y >= 0 && y < GetHeightCount(name))
	{
		SimpleCraft::ItemContent itemContent = SimpleCraft::ItemContent{ "air", 0 };
		StackItems(itemContent, (*item)[x + y * widthCount], limit);
		return itemContent;
	}
	return SimpleCraft::ItemContent{ "air", 0 };
}
SimpleCraft::ItemContent* SimpleCraft::Item::GetItemPointer(std::string_view name, unsigned int x, unsigned int y)
{
	unsigned int widthCount = GetWidthCount(name);
	std::vector<SimpleCraft::ItemContent>* item = GetItemList(name);
	if (!item)
	{
		return nullptr;
	}
	if (x >= 0 && x < widthCount && y >= 0 && y < GetHeightCount(name))
	{
		return &(*item)[x + y * widthCount];
	}
	return nullptr;
}
void SimpleCraft::Item::SetItem(std::string_view name, unsigned int x, unsigned int y, const SimpleCraft::ItemContent& value)
{
	unsigned int widthCount = GetWidthCount(name);
	std::vector<SimpleCraft::ItemContent>* item = GetItemList(name);
	if (!item)
	{
		return;
	}
	if (x >= 0 && x < widthCount && y >= 0 && y < GetHeightCount(name))
	{
		unsigned int index = x + y * widthCount;
		(*item)[index] = value;
	}
}
void SimpleCraft::Item::SetItem(std::string_view name, unsigned int x, unsigned int y, SimpleCraft::ItemContent& value, unsigned int limit)
{
	unsigned int widthCount = GetWidthCount(name);
	std::vector<SimpleCraft::ItemContent>* item = GetItemList(name);
	if (!item)
	{
		return;
	}
	if (x >= 0 && x < widthCount && y >= 0 && y < GetHeightCount(name))
	{
		unsigned int index = x + y * widthCount;
		StackItems((*item)[index], value, limit);
	}
}
bool SimpleCraft::Item::AddItem(const std::vector<std::string_view>& names, std::string_view value)
{
	for (std::string_view name : names)
	{
		std::vector<SimpleCraft::ItemContent>* item = GetItemList(name);
		if (item)
		{
			for (unsigned int i = 0; i < item->size(); i++)
			{
				if ((*item)[i].name == std::string(value) && (*item)[i].count < _stackCount)
				{
					(*item)[i].count += 1;
					return true;
				}
			}
			for (unsigned int i = 0; i < item->size(); i++)
			{
				if ((*item)[i].name == "air")
				{
					(*item)[i].name = std::string(value);
					(*item)[i].count = 1;
					return true;
				}
			}
		}
	}
	return false;
}
void SimpleCraft::Item::AddItems(const std::vector<std::string_view>& names, SimpleCraft::ItemContent& value)
{
	for (std::string_view name : names)
	{
		std::vector<SimpleCraft::ItemContent>* item = GetItemList(name);
		if (item)
		{
			for (unsigned int i = 0; i < item->size(); i++)
			{
				if ((*item)[i].name == value.name && (*item)[i].count < _stackCount)
				{
					StackItems((*item)[i], value);
					if (value.count < 1)
					{
						return;
					}
				}
			}
			for (unsigned int i = 0; i < item->size(); i++)
			{
				if ((*item)[i].name == "air")
				{
					StackItems((*item)[i], value);
					if (value.count < 1)
					{
						return;
					}
				}
			}
		}
	}
}
void SimpleCraft::Item::StackItems(SimpleCraft::ItemContent& valueSelf, SimpleCraft::ItemContent& valueOther, unsigned int limit)
{
	if (valueOther.count < 1 || (valueSelf.name != valueOther.name && valueSelf.name != "air"))
	{
		return;
	}
	unsigned int count = valueSelf.count + valueOther.count;
	unsigned int toStack = valueOther.count;
	if (limit > 0)
	{
		toStack = glm::min(limit, valueOther.count);
		count = valueSelf.count + toStack;
	}
	if (valueSelf.name == "air")
	{
		valueSelf.name = valueOther.name;
	}
	if (count > _stackCount)
	{
		valueOther.count -= std::min(_stackCount - valueSelf.count, toStack);
		valueSelf.count = _stackCount;
	}
	if (count <= _stackCount)
	{
		valueSelf.count = count;
		valueOther.count -= toStack;
	}
	if (valueOther.count < 1)
	{
		valueOther.name = "air";
		valueOther.count = 0;
	}
}
void SimpleCraft::Item::StackItems(std::string_view name, unsigned int x, unsigned int y, SimpleCraft::ItemContent& value, unsigned int limit)
{
	SimpleCraft::ItemContent* itemContent = GetItemPointer(name, x, y);
	if (!itemContent)
	{
		return;
	}
	StackItems(*itemContent, value, limit);
}
void SimpleCraft::Item::StackItems(SimpleCraft::ItemContent* valueSelf, SimpleCraft::ItemContent& valueOther, unsigned int limit)
{
	if (!valueSelf)
	{
		return;
	}
	StackItems(*valueSelf, valueOther, limit);
}
std::string SimpleCraft::Item::DeleteItem(std::string_view name)
{
	if (std::unordered_map<std::string, std::vector<SimpleCraft::ItemContent>>::iterator it = _items.find(std::string(name)); it != _items.end())
	{
		if (_chooseSlot >= it->second.size() || it->second[_chooseSlot].name == "air")
		{
			return "air";
		}
		std::string itemName = it->second[_chooseSlot].name;
		it->second[_chooseSlot].count--;
		if (it->second[_chooseSlot].count < 1)
		{
			it->second[_chooseSlot].name = "air";
		}
		return itemName;
	}
	return "air";
}
unsigned int SimpleCraft::Item::GetWidthCount(std::string_view name) const
{
	if (std::unordered_map<std::string, unsigned int>::const_iterator it = _widthCounts.find(std::string(name)); it != _widthCounts.end())
	{
		return it->second;
	}
	return unsigned int{};
}
unsigned int SimpleCraft::Item::GetHeightCount(std::string_view name) const
{
	if (std::unordered_map<std::string, unsigned int>::const_iterator it = _heightCounts.find(std::string(name)); it != _heightCounts.end())
	{
		return it->second;
	}
	return unsigned int{};
}
glm::vec2 SimpleCraft::Item::GetOffset(std::string_view name) const
{
	if (std::unordered_map<std::string, glm::vec2>::const_iterator it = _offsets.find(std::string(name)); it != _offsets.end())
	{
		return it->second;
	}
	return glm::vec2{};
}
glm::vec2 SimpleCraft::Item::GetSpace(std::string_view name) const
{
	if (std::unordered_map<std::string, glm::vec2>::const_iterator it = _spaces.find(std::string(name)); it != _spaces.end())
	{
		return it->second;
	}
	return glm::vec2{};
}
SimpleCraft::ItemGrid SimpleCraft::Item::GetItemGrid(std::string_view name) const
{
	if (std::unordered_map<std::string, SimpleCraft::ItemGrid>::const_iterator it = _itemGrids.find(std::string(name)); it != _itemGrids.end())
	{
		return it->second;
	}
	return SimpleCraft::ItemGrid{};
}