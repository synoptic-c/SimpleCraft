#include"FontRender.hpp"
void SimpleCraft::FontRender::RenderText(const SimpleCraft::Mesh* mesh, SimpleCraft::Shader* shader, const SimpleCraft::Font* font, std::string_view text, glm::vec2 position, glm::vec2 scale)
{
	for (unsigned int i = 0; i < text.size(); i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(position, 0.0f));
		model = glm::scale(model, glm::vec3(scale, 0.0f));
		shader->SetMat4("u_model", model);
		font->Bind(text[i]);
		mesh->Draw();
		position.x += scale.x;
	}
}