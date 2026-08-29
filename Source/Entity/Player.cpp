#include"Player.hpp"
SimpleCraft::Player::Player(std::string_view configPath) : _position{}, _speed{}, _direction{}, _walkSpeed{}, _gravity{}, _falling{}, _hangTime{}, _jumpSpeed{}
{
	std::fstream configFile(std::string(configPath), std::ios::in);
	if (!configFile)
	{
		PRINT_ERROR_FILE("Failed to open file", configPath);
		return;
	}
	nlohmann::json configJson = nlohmann::json::parse(configFile);
	configFile.close();
	_texture = std::make_unique<SimpleCraft::Texture>(configJson["texturePath"].get<std::string_view>());
	_atlas = std::make_unique<SimpleCraft::Atlas>(configJson["atlasPath"].get<std::string_view>());
	_animation = std::make_unique<SimpleCraft::Animation>(configJson["animationPath"].get<std::string_view>());
	_walkSpeed = configJson["walkSpeed"].get<float>();
	_gravity = configJson["gravity"].get<float>();
	_hangTime = configJson["hangTime"].get<float>();
	_jumpSpeed = configJson["jumpSpeed"].get<float>();
	_position = glm::vec2(0.0f, 5.0f);
}
void SimpleCraft::Player::Update(const SimpleCraft::BoundManager& boundManager, SimpleCraft::World& world, const SimpleCraft::Tile& tile, const SimpleCraft::Input& input, float deltaTime)
{
	SimpleCraft::Bound bound = boundManager.GetBound("humanoid");
	bool left = input.GetLeft();
	bool right = input.GetRight();
	bool up = input.GetUp();
	_speed.x = (right - left) * _walkSpeed;
	_position.x += _speed.x * deltaTime;
	if (SimpleCraft::Collision::TileResolveCollision(bound, world, tile, _position, glm::vec2(_speed.x, float{})))
	{
		_speed.x = float{};
	}
	_speed.y -= _gravity * deltaTime;
	_falling += deltaTime;
	if (_falling < _hangTime && up)
	{
		_speed.y = _jumpSpeed;
	}
	_position.y += _speed.y * deltaTime;
	if (SimpleCraft::Collision::TileResolveCollision(bound, world, tile, _position, glm::vec2(float{}, _speed.y)))
	{
		if (_speed.y < 0.0f)
		{
			_falling = float{};
		}
		_speed.y = float{};
	}
}
void SimpleCraft::Player::Render(const SimpleCraft::MeshManager& meshManager, SimpleCraft::ShaderManager& shaderManager, const SimpleCraft::Camera& camera, float deltaTime)
{
	const SimpleCraft::Mesh* mesh = meshManager.GetMesh("quad");
	SimpleCraft::Shader* shader = shaderManager.GetShader("atlas");
	if (!mesh || !shader || !_texture)
	{
		return;
	}
	mesh->Bind();
	shader->Use();
	shader->SetMat4("u_projection", camera.GetProjection());
	shader->SetMat4(
		"u_view", 
		glm::translate(
			glm::mat4(1.0f),
			glm::vec3(
				-camera.GetView().x + (camera.GetReferenceRight() + camera.GetReferenceLeft()) * 0.5f,
				-camera.GetView().y + (camera.GetReferenceTop() + camera.GetReferenceBottom()) * 0.5f,
				float{}
			)
		)
	);
	_texture->Bind(unsigned int{});
	for (const std::string& name : _animation->GetNames())
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(_position + _animation->GetOffset(name), float{}));
		if (glm::abs(_speed.x) > float{})
		{
			_direction = glm::radians(glm::sign(_speed.x) > float{} ? float{} : 180.0f);
		}
		model = glm::rotate(model, _direction, glm::vec3(float{}, 1.0f, float{}));
		if (name == "leftHand" || name == "leftLeg" || name == "rightHand" || name == "rightLeg")
		{
			model = _animation->Swing(model, _speed, name, deltaTime);
		}
		model = glm::scale(model, glm::vec3(_animation->GetScale(name), float{}));
		shader->SetMat4("u_model", model);
		shader->SetVec2("u_uvOffset", _atlas->GetUvOffset(name));
		shader->SetVec2("u_uvIndex", _atlas->GetUvIndex(name));
		shader->SetVec2("u_uvScale", _atlas->GetUvScale(name));
		mesh->Draw();
	}
}
glm::vec2 SimpleCraft::Player::GetPosition() const
{
	return _position;
}