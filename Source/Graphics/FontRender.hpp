#pragma once
#include<string>
#include<string_view>
#include<glm/glm.hpp>
#include"Graphics/Mesh.hpp"
#include"Graphics/Shader.hpp"
#include"Graphics/Font.hpp"
#include"Graphics/Camera.hpp"
namespace SimpleCraft
{
	class FontRender
	{
	private:

	public:
		static void RenderText(const SimpleCraft::Mesh* mesh, SimpleCraft::Shader* shader, const SimpleCraft::Font* font, std::string_view text, glm::vec2 position, glm::vec2 scale);
	};
}