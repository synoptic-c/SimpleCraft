#pragma once
#include<unordered_map>
#include<string>
#include<string_view>
#include<fstream>
#include<nlohmann/json.hpp>
#include"Graphics/Font.hpp"
#include"Util/Log.hpp"
namespace SimpleCraft
{
	class FontManager
	{
	private:
		std::unordered_map<std::string, SimpleCraft::Font> _fonts;
		float _quality;
	public:
		FontManager(std::string_view path);
		const SimpleCraft::Font* GetFont(std::string_view path) const;
	};
}