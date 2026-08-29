#include"Drop.hpp"
SimpleCraft::Drop::Drop(std::string_view path) : _scale{}, _gravity{}
{
	std::fstream file(std::string(path), std::ios::in);
	if (!file)
	{
		PRINT_ERROR_FILE("Failed to open file", path);
		return;
	}
	nlohmann::json json = nlohmann::json::parse(file);
	file.close();
	_scale = glm::vec2(json["scale"]["x"].get<float>(), json["scale"]["y"].get<float>());
	_gravity = json["gravity"].get<float>();
}
void SimpleCraft::Drop::Update(const SimpleCraft::BoundManager& boundManager, SimpleCraft::World& world, const SimpleCraft::Tile& tile, const SimpleCraft::Player& player, SimpleCraft::Item& item, float deltaTime)
{
	SimpleCraft::Bound dropShapeBound = boundManager.GetBound("dropShape");
	SimpleCraft::Bound humanoidBound = boundManager.GetBound("humanoid");
	for (unsigned int i = 0; i < _positions.size();)
	{
		if (SimpleCraft::Collision::TileResolveCollision(dropShapeBound, world, tile, _positions[i], glm::vec2(_speeds[i].x, 0.0f)))
		{
			_speeds[i].x = float{};
		}
		_speeds[i].y -= _gravity * deltaTime;
		_positions[i].y += _speeds[i].y * deltaTime;
		if (SimpleCraft::Collision::TileResolveCollision(dropShapeBound, world, tile, _positions[i], glm::vec2(0.0f, _speeds[i].y)))
		{
			_speeds[i].y = float{};
		}
		if (SimpleCraft::Overlap::Check(dropShapeBound, humanoidBound, _positions[i], player.GetPosition()))
		{
			if (item.AddItem({ "quickSlotItems", "backpackItems" }, _names[i]))
			{
				Delete(i);
			}
			else
			{
				++i;
			}
		}
		else
		{
			++i;
		}
	}
}
void SimpleCraft::Drop::Render(const SimpleCraft::MeshManager& meshManager, SimpleCraft::ShaderManager& shaderManager, SimpleCraft::Tile& tile, const SimpleCraft::Camera& camera)
{
	const SimpleCraft::Mesh* mesh = meshManager.GetMesh("quad");
	SimpleCraft::Shader* shader = shaderManager.GetShader("basic");
	if (!mesh || !shader || !tile.GetTextures().size())
	{
		return;
	}
	mesh->Bind();
	shader->Use();
	shader->SetMat4("u_projection", camera.GetProjection());
	shader->SetMat4("u_view",
		glm::translate(
			glm::mat4(1.0f),
			glm::vec3(
				-camera.GetView().x + (camera.GetReferenceRight() + camera.GetReferenceLeft()) * 0.5f,
				-camera.GetView().y + (camera.GetReferenceTop() + camera.GetReferenceBottom()) * 0.5f,
				0.0f
			)
		)
	);
	for (unsigned int i = 0; i < _names.size(); i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(_positions[i], 0.0f));
		model = glm::scale(model, glm::vec3(_scale, 0.0f));
		shader->SetMat4("u_model", model);
		int index = -1;
		if (int tempIndex = tile.GetTileDefinition(_names[i]); tempIndex > -1)
		{
			index = tempIndex;
		}
		if (index > -1)
		{
			tile.GetTextures()[index].Bind(unsigned int{});
			mesh->Draw();
		}
	}
}
void SimpleCraft::Drop::Add(glm::vec2 position, const std::string& name)
{
	_positions.emplace_back(position);
	_speeds.emplace_back(glm::vec2(float{}, float{}));
	_names.emplace_back(name);
}
void SimpleCraft::Drop::Add(glm::vec2 position, const std::string* name)
{
	if (!name)
	{
		return;
	}
	_positions.emplace_back(position);
	_speeds.emplace_back(glm::vec2(float{}, float{}));
	_names.emplace_back(*name);
}
void SimpleCraft::Drop::Delete(unsigned int index)
{
	if (index >= _positions.size())
	{
		return;
	}
	_positions.erase(_positions.begin() + index);
	_speeds.erase(_speeds.begin() + index);
	_names.erase(_names.begin() + index);
}