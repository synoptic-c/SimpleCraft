#include"VertexArray.hpp"
SimpleCraft::VertexArray::VertexArray() : _vertexArray{}
{
	glCreateVertexArrays(1, &_vertexArray);
}
SimpleCraft::VertexArray::~VertexArray()
{
	if (_vertexArray)
	{
		glDeleteVertexArrays(1, &_vertexArray);
	}
}
SimpleCraft::VertexArray::VertexArray(SimpleCraft::VertexArray&& other) noexcept : _vertexArray(other._vertexArray)
{
	other._vertexArray = unsigned int{};
}
SimpleCraft::VertexArray& SimpleCraft::VertexArray::operator=(SimpleCraft::VertexArray&& other) noexcept
{
	if (this != &other)
	{
		if (_vertexArray)
		{
			glDeleteVertexArrays(1, &_vertexArray);
		}
		_vertexArray = other._vertexArray;
		other._vertexArray = unsigned int{};
	}
	return *this;
}
void SimpleCraft::VertexArray::Bind() const
{
	if (_vertexArray)
	{
		glBindVertexArray(_vertexArray);
	}
}
void SimpleCraft::VertexArray::VertexArrayAttribFormat(unsigned int attribindex, unsigned int size, unsigned int type, unsigned char normalized, unsigned int relativeoffset)
{
	if (_vertexArray)
	{
		glVertexArrayAttribFormat(_vertexArray, attribindex, size, type, normalized, relativeoffset);
	}
}
void SimpleCraft::VertexArray::VertexArrayAttribBinding(unsigned int attribindex, unsigned int bindingindex)
{
	if (_vertexArray)
	{
		glVertexArrayAttribBinding(_vertexArray, attribindex, bindingindex);
	}
}
void SimpleCraft::VertexArray::VertexArrayVertexBuffer(unsigned int bindingindex, unsigned int buffer, GLintptr offset, int stride)
{
	if (_vertexArray)
	{
		glVertexArrayVertexBuffer(_vertexArray, bindingindex, buffer, offset, stride);
	}
}
void SimpleCraft::VertexArray::EnableVertexAttribArray(unsigned int index)
{
	if (_vertexArray)
	{
		glEnableVertexArrayAttrib(_vertexArray, index);
	}
}
void SimpleCraft::VertexArray::VertexArrayElementBuffer(unsigned int buffer)
{
	if (_vertexArray)
	{
		glVertexArrayElementBuffer(_vertexArray, buffer);
	}
}