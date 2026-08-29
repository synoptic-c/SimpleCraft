#include"VertexBuffer.hpp"
SimpleCraft::VertexBuffer::VertexBuffer() : _vertexBuffer{}
{
	glCreateBuffers(1, &_vertexBuffer);
}
SimpleCraft::VertexBuffer::~VertexBuffer()
{
	if (_vertexBuffer)
	{
		glDeleteBuffers(1, &_vertexBuffer);
	}
}
SimpleCraft::VertexBuffer::VertexBuffer(SimpleCraft::VertexBuffer&& other) noexcept : _vertexBuffer(other._vertexBuffer)
{
	other._vertexBuffer = unsigned int{};
}
SimpleCraft::VertexBuffer& SimpleCraft::VertexBuffer::operator=(SimpleCraft::VertexBuffer&& other) noexcept
{
	if (this != &other)
	{
		if (_vertexBuffer)
		{
			glDeleteBuffers(1, &_vertexBuffer);
		}
		_vertexBuffer = other._vertexBuffer;
		other._vertexBuffer = unsigned int{};
	}
	return *this;
}
unsigned int SimpleCraft::VertexBuffer::GetVertexBuffer() const
{
	return _vertexBuffer;
}
void SimpleCraft::VertexBuffer::NamedBufferData(GLsizeiptr size, const void* data, unsigned int usage)
{
	if (_vertexBuffer)
	{
		glNamedBufferData(_vertexBuffer, size, data, usage);
	}
}