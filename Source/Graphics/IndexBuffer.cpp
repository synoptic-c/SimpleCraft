#include"IndexBuffer.hpp"
SimpleCraft::IndexBuffer::IndexBuffer() : _indexBuffer{}
{
	glCreateBuffers(1, &_indexBuffer);
}
SimpleCraft::IndexBuffer::~IndexBuffer()
{
	if (_indexBuffer)
	{
		glDeleteBuffers(1, &_indexBuffer);
	}
}
SimpleCraft::IndexBuffer::IndexBuffer(SimpleCraft::IndexBuffer&& other) noexcept : _indexBuffer(other._indexBuffer)
{
	other._indexBuffer = unsigned int{};
}
SimpleCraft::IndexBuffer& SimpleCraft::IndexBuffer::operator=(SimpleCraft::IndexBuffer&& other) noexcept
{
	if (this != &other)
	{
		if (_indexBuffer)
		{
			glDeleteBuffers(1, &_indexBuffer);
		}
		_indexBuffer = other._indexBuffer;
		other._indexBuffer = unsigned int{};
	}
	return *this;
}
unsigned int SimpleCraft::IndexBuffer::GetIndexBuffer() const
{
	return _indexBuffer;
}
void SimpleCraft::IndexBuffer::NamedBufferData(GLsizeiptr size, const void* data, unsigned int usage)
{
	if (_indexBuffer)
	{
		glNamedBufferData(_indexBuffer, size, data, usage);
	}
}