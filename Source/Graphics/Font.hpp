#pragma once
#include<unordered_map>
#include<string_view>
#include<string>
#include<vector>
#include<fstream>
#include<glad/glad.h>
#include<nlohmann/json.hpp>
#include<stb_truetype.h>
#include"Graphics/Texture.hpp"
#include"Util/Log.hpp"
namespace SimpleCraft
{
	class Font
	{
	private:
		std::unordered_map<char, SimpleCraft::Texture> _textures;
	public:
		Font(std::string_view path, float quality);
		void Bind(char font) const;
	};
}