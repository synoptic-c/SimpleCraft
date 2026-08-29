#include"Animation.hpp"
void SimpleCraft::from_json(const nlohmann::json& json, SimpleCraft::AnimationDefinition& animationDefinition)
{
	json["offset"]["x"].get_to<float>(animationDefinition.offset.x);
	json["offset"]["y"].get_to<float>(animationDefinition.offset.y);
	json["scale"]["x"].get_to<float>(animationDefinition.scale.x);
	json["scale"]["y"].get_to<float>(animationDefinition.scale.y);
	json["rotateCenter"]["x"].get_to<float>(animationDefinition.rotateCenter.x);
	json["rotateCenter"]["y"].get_to<float>(animationDefinition.rotateCenter.y);
	json["side"].get_to<std::string>(animationDefinition.side);
	json["swingSpeed"].get_to<float>(animationDefinition.swingSpeed);
	json["amplitude"].get_to<float>(animationDefinition.amplitude);
}
SimpleCraft::Animation::Animation(std::string_view path) : _leftSide{}, _rightSide{}, _phase{}
{
	std::fstream file(std::string(path), std::ios::in);
	if (!file)
	{
		PRINT_ERROR_FILE("Failed to open file", path);
		return;
	}
	nlohmann::json json = nlohmann::json::parse(file);
	file.close();
	_leftSide = json["leftSide"].get<float>();
	_rightSide = json["rightSide"].get<float>();
	_names = json["names"].get<std::vector<std::string>>();
	_animationDefinitions = json["animationDefinitions"].get<std::unordered_map<std::string, SimpleCraft::AnimationDefinition>>();
}
glm::mat4 SimpleCraft::Animation::Swing(glm::mat4 model, glm::vec2 speed, std::string_view name, float deltaTime)
{
	if (glm::abs(speed.x) > float{})
	{
		_phase += deltaTime;
	}
	else
	{
		_phase = float{};
	}
	model = glm::translate(model, glm::vec3(GetRotateCenter(name), float{}));
	float sideValue{};
	if (const std::string* sideName = GetSide(name); sideName)
	{
		if (*sideName == "left")
		{
			sideValue = _leftSide;
		}
		else if (*sideName == "right")
		{
			sideValue = _rightSide;
		}
	}
	model = glm::rotate(model, std::sin(_phase * GetSwingSpeed(name)) * GetAmplitude(name) * sideValue, glm::vec3(float{}, float{}, 1.0f));
	model = glm::translate(model, glm::vec3(-GetRotateCenter(name), float{}));
	return model;
}
glm::vec2 SimpleCraft::Animation::GetOffset(std::string_view name) const
{
	if (std::unordered_map<std::string, SimpleCraft::AnimationDefinition>::const_iterator it = _animationDefinitions.find(std::string(name)); it != _animationDefinitions.end())
	{
		return it->second.offset;
	}
	return glm::vec2{};
}
glm::vec2 SimpleCraft::Animation::GetScale(std::string_view name) const
{
	if (std::unordered_map<std::string, SimpleCraft::AnimationDefinition>::const_iterator it = _animationDefinitions.find(std::string(name)); it != _animationDefinitions.end())
	{
		return it->second.scale;
	}
	return glm::vec2{};
}
glm::vec2 SimpleCraft::Animation::GetRotateCenter(std::string_view name) const
{
	if (std::unordered_map<std::string, SimpleCraft::AnimationDefinition>::const_iterator it = _animationDefinitions.find(std::string(name)); it != _animationDefinitions.end())
	{
		return it->second.rotateCenter;
	}
	return glm::vec2{};
}
const std::string* SimpleCraft::Animation::GetSide(std::string_view name) const
{
	if (std::unordered_map<std::string, SimpleCraft::AnimationDefinition>::const_iterator it = _animationDefinitions.find(std::string(name)); it != _animationDefinitions.end())
	{
		return &it->second.side;
	}
	return nullptr;
}
float SimpleCraft::Animation::GetSwingSpeed(std::string_view name) const
{
	if (std::unordered_map<std::string, SimpleCraft::AnimationDefinition>::const_iterator it = _animationDefinitions.find(std::string(name)); it != _animationDefinitions.end())
	{
		return it->second.swingSpeed;
	}
	return float{};
}
float SimpleCraft::Animation::GetAmplitude(std::string_view name) const
{
	if (std::unordered_map<std::string, SimpleCraft::AnimationDefinition>::const_iterator it = _animationDefinitions.find(std::string(name)); it != _animationDefinitions.end())
	{
		return it->second.amplitude;
	}
	return float{};
}
const std::vector<std::string>& SimpleCraft::Animation::GetNames() const
{
	return _names;
}
void SimpleCraft::Animation::AddPhase(float phase)
{
	_phase += phase;
}
void SimpleCraft::Animation::SetPhase(float phase)
{
	_phase = phase;
}
float SimpleCraft::Animation::GetPhase() const
{
	return _phase;
}