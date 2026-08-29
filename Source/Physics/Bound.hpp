#pragma once
#include<nlohmann/json.hpp>
namespace SimpleCraft
{
	struct Bound
	{
		float left{};
		float right{};
		float bottom{};
		float top{};
	};
	void from_json(const nlohmann::json& json, SimpleCraft::Bound& bound);
}