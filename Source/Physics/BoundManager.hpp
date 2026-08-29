#pragma once
#include<unordered_map>
#include<string>
#include<string_view>
#include<fstream>
#include<nlohmann/json.hpp>
#include"Bound.hpp"
#include"Util/Log.hpp"
namespace SimpleCraft
{
	class BoundManager
	{
	private:
		std::unordered_map<std::string, SimpleCraft::Bound> _bounds;
		static SimpleCraft::Bound LoadBound(std::string_view path);
	public:
		BoundManager(std::string_view path);
		SimpleCraft::Bound GetBound(std::string_view name) const;
	};
}