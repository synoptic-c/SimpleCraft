#include"Texture.hpp"
SimpleCraft::Texture::Texture(std::string_view path)
{
	int width;
	int height;
	int channels;
	unsigned char* data = stbi_load(std::string(path).c_str(), &width, &height, &channels, int{});
	if (!data)
	{
		PRINT_ERROR_FILE("Failed to open file", path);
		_texture = unsigned int{};
		return;
	}
	unsigned int internalformat = unsigned int{};
	unsigned int format = unsigned int{};
	if (channels == 1)
	{
		internalformat = GL_R8;
		format = GL_RED;
	}
	if (channels == 2)
	{
		internalformat = GL_RG8;
		format = GL_RG;
	}
	if (channels == 3)
	{
		internalformat = GL_RGB8;
		format = GL_RGB;
	}
	if (channels == 4)
	{
		internalformat = GL_RGBA8;
		format = GL_RGBA;
	}
	CreateTexture(width, height, data, internalformat, format, true, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
	stbi_image_free(data);
}
SimpleCraft::Texture::Texture(int width, int height, unsigned char* bitmap, unsigned int internalformat, unsigned int format)
{
	if (!bitmap)
	{
		PRINT_ERROR("Texture bitmap is nullptr");
		_texture = 0;
		return;
	}
	CreateTexture(width, height, bitmap, internalformat, format, false, GL_NEAREST, GL_NEAREST);
}
SimpleCraft::Texture::~Texture()
{
	if (_texture)
	{
		glDeleteTextures(1, &_texture);
	}
}
SimpleCraft::Texture::Texture(Texture&& other) noexcept : _texture(other._texture)
{
	other._texture = unsigned int{};
}
SimpleCraft::Texture& SimpleCraft::Texture::operator=(SimpleCraft::Texture&& other) noexcept
{
	if (this != &other)
	{
		if (_texture)
		{
			glDeleteTextures(1, &_texture);
		}
		_texture = other._texture;
		other._texture = unsigned int{};
	}
	return *this;
}
void SimpleCraft::Texture::CreateTexture(int width, int height, unsigned char* data, unsigned int internalformat, unsigned int format, bool useMinmap, int minFilter, int magFilter)
{
	glCreateTextures(GL_TEXTURE_2D, 1, &_texture);
	int levels = 0;
	if (useMinmap)
	{
		levels = (int)std::log2(std::max(width, height));
	}
	glTextureStorage2D(_texture, 1 + levels, internalformat, width, height);
	glTextureSubImage2D(_texture, int{}, int{}, int{}, width, height, format, GL_UNSIGNED_BYTE, data);
	glTextureParameteri(_texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(_texture, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(_texture, GL_TEXTURE_MIN_FILTER, minFilter);
	glTextureParameteri(_texture, GL_TEXTURE_MAG_FILTER, magFilter);
	if (useMinmap)
	{
		glGenerateTextureMipmap(_texture);
	}
}
void SimpleCraft::Texture::Bind(unsigned int unit) const
{
	if (_texture)
	{
		glBindTextureUnit(unit, _texture);
	}
}