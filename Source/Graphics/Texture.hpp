#pragma once
#include<cmath>
#include<string>
#include<string_view>
#include<glad/glad.h>
#include<stb_image.h>
#include"Util/Log.hpp"
namespace SimpleCraft
{
	class Texture
	{
	private:
		unsigned int _texture;
	public:
		Texture(std::string_view path);
		Texture(int width, int height, unsigned char* bitmap, unsigned int internalformat, unsigned int format);
		~Texture();
		Texture(const Texture&) = delete;
		SimpleCraft::Texture& operator=(const SimpleCraft::Texture&) = delete;
		Texture(SimpleCraft::Texture&& other) noexcept;
		SimpleCraft::Texture& operator=(SimpleCraft::Texture&& other) noexcept;
		void CreateTexture(int width, int height, unsigned char* data, unsigned int internalformat, unsigned int format, bool useMinmap, int minFilter, int magFilter);
		void Bind(unsigned int unit) const;
	};
}