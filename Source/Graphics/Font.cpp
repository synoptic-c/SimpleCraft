#include"Font.hpp"
SimpleCraft::Font::Font(std::string_view path, float quality)
{
	stbtt_fontinfo fontinfo;
	std::fstream fileFont(std::string(path), std::ios::in | std::ios::binary);
	if (!fileFont)
	{
		PRINT_ERROR_FILE("Failed to open file", path);
		return;
	}
	std::vector<unsigned char> data{
		std::istreambuf_iterator<char>(fileFont),
		std::istreambuf_iterator<char>()
	};
	if (!stbtt_InitFont(&fontinfo, data.data(), 0))
	{
		PRINT_ERROR("Failed to init font");
		return;
	}
	float scale = stbtt_ScaleForPixelHeight(&fontinfo, quality);
	std::string fontLibraries;
	for (char i = 'a'; i <= 'z'; i++)
	{
		fontLibraries += i;
	}
	for (char i = 'A'; i <= 'Z'; i++)
	{
		fontLibraries += i;
	}
	for (char i = '0'; i <= '9'; i++)
	{
		fontLibraries += i;
	}
	for (char fontLibrary : fontLibraries)
	{
		int width;
		int height;
		int xoff;
		int yoff;
		unsigned char* bitmap = stbtt_GetCodepointBitmap(&fontinfo, 0.0f, scale, fontLibrary, &width, &height, &xoff, &yoff);
		if (bitmap)
		{
			_textures.emplace(std::piecewise_construct, std::forward_as_tuple(fontLibrary), std::forward_as_tuple(width, height, bitmap, GL_R8, GL_RED));
			stbtt_FreeBitmap(bitmap, nullptr);
		}
	}
}
void SimpleCraft::Font::Bind(char font) const
{
	if (std::unordered_map<char, SimpleCraft::Texture>::const_iterator it = _textures.find(font); it != _textures.end())
	{
		it->second.Bind(unsigned int{});
	}
}