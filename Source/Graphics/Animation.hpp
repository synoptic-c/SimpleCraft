#pragma once
#include<unordered_map>
#include<vector>
#include<string>
#include<string_view>
#include<fstream>
#include<cmath>
#include<nlohmann/json.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"Util/Log.hpp"
namespace SimpleCraft
{
	struct AnimationDefinition
	{
		glm::vec2 offset{};
		glm::vec2 scale{};
		glm::vec2 rotateCenter{};
		std::string side;
		float swingSpeed{};
		float amplitude{};
	};
	void from_json(const nlohmann::json& json, SimpleCraft::AnimationDefinition& animationDefinition);
	class Animation
	{
	private:
		std::unordered_map<std::string, AnimationDefinition> _animationDefinitions;
		std::vector<std::string> _names;
		float _leftSide;
		float _rightSide;
		float _phase;
	public:
		Animation(std::string_view path);
		glm::mat4 Swing(glm::mat4 model, glm::vec2 speed, std::string_view name, float deltaTime);
		glm::vec2 GetOffset(std::string_view name) const;
		glm::vec2 GetScale(std::string_view name) const;
		glm::vec2 GetRotateCenter(std::string_view name) const;
		const std::string* GetSide(std::string_view name) const;
		float GetSwingSpeed(std::string_view name) const;
		float GetAmplitude(std::string_view name) const;
		const std::vector<std::string>& GetNames() const;
		void AddPhase(float phase);
		void SetPhase(float phase);
		float GetPhase() const;
	};
}