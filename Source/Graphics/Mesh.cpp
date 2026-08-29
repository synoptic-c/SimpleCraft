#include"Mesh.hpp"
SimpleCraft::Mesh::Mesh(std::string_view path) : _count{}
{
	std::fstream file(std::string(path), std::ios::in);
	if (!file)
	{
		PRINT_ERROR_FILE("Failed to open file", path);
		return;
	}
	nlohmann::json json = nlohmann::json::parse(file);
	file.close();
	std::vector<float> vertices = json["vertices"].get<std::vector<float>>();
	std::vector<unsigned int> indices = json["indices"].get<std::vector<unsigned int>>();
	std::vector<int> layouts = json["layouts"].get<std::vector<int>>();
	_vertexBuffer.NamedBufferData(vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	_indexBuffer.NamedBufferData(indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	int stride{};
	for (int layout : layouts)
	{
		stride += layout;
	}
	_vertexArray.VertexArrayVertexBuffer(unsigned int{}, _vertexBuffer.GetVertexBuffer(), GLintptr{}, sizeof(float) * stride);
	int offset{};
	for (int i = 0; i < layouts.size(); i++)
	{
		_vertexArray.VertexArrayAttribFormat(i, layouts[i], GL_FLOAT, GL_FALSE, sizeof(float) * offset);
		_vertexArray.VertexArrayAttribBinding(i, unsigned int{});
		_vertexArray.EnableVertexAttribArray(i);
		offset += layouts[i];
	}
	_vertexArray.VertexArrayElementBuffer(_indexBuffer.GetIndexBuffer());
	_count = (int)indices.size();
}
void SimpleCraft::Mesh::Bind() const
{
	_vertexArray.Bind();
}
void SimpleCraft::Mesh::Draw() const
{
	if (_vertexBuffer.GetVertexBuffer())
	{
		glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, nullptr);
	}
}
int SimpleCraft::Mesh::GetCount() const
{
	return _count;
}