#include"Inventory.hpp"
SimpleCraft::Inventory::Inventory(std::string_view path) : _scale{}
{
	std::fstream file(std::string(path), std::ios::in);
	if (!file)
	{
		PRINT_ERROR_FILE("Failed to open file", path);
		return;
	}
	nlohmann::json json = nlohmann::json::parse(file);
	file.close();
	_texture = std::make_unique<SimpleCraft::Texture>(json["texturePath"].get<std::string_view>());
	_atlas = std::make_unique<SimpleCraft::Atlas>(json["atlasPath"].get<std::string_view>());
	_scale = glm::vec2(json["scale"]["x"].get<float>(), json["scale"]["y"].get<float>());
}
void SimpleCraft::Inventory::Render(bool isInventory, const SimpleCraft::MeshManager& meshManager, SimpleCraft::ShaderManager& shaderManager, const SimpleCraft::Camera& camera)
{
	if (!isInventory)
	{
		return;
	}
	const SimpleCraft::Mesh* mesh = meshManager.GetMesh("quad");
	SimpleCraft::Shader* shader = shaderManager.GetShader("atlas");
	if (!mesh || !shader || !_texture)
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
				(camera.GetReferenceRight() + camera.GetReferenceLeft()) * 0.5f,
				(camera.GetReferenceTop() + camera.GetReferenceBottom()) * 0.5f,
				float{}
			)
		)
	);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(_scale, 0.0f));
	shader->SetMat4("u_model", model);
	shader->SetVec2("u_uvOffset", _atlas->GetUvOffset("inventory"));
	shader->SetVec2("u_uvIndex", _atlas->GetUvIndex("inventory"));
	shader->SetVec2("u_uvScale", _atlas->GetUvScale("inventory"));
	_texture->Bind(unsigned int{});
	mesh->Draw();
}