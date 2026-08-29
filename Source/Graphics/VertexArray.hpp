#pragma once
#include<glad/glad.h>
namespace SimpleCraft
{
	class VertexArray
	{
	private:
		unsigned int _vertexArray;
	public:
		VertexArray();
		~VertexArray();
		VertexArray(const SimpleCraft::VertexArray&) = delete;
		SimpleCraft::VertexArray& operator=(const SimpleCraft::VertexArray&) = delete;
		VertexArray(SimpleCraft::VertexArray&& other) noexcept;
		SimpleCraft::VertexArray& operator=(SimpleCraft::VertexArray&& other) noexcept;
		void Bind() const;
		void VertexArrayAttribFormat(unsigned int attribindex, unsigned int size, unsigned int type, unsigned char normalized, unsigned int relativeoffset);
		void VertexArrayAttribBinding(unsigned int attribindex, unsigned int bindingindex);
		void VertexArrayVertexBuffer(unsigned int bindingindex, unsigned int buffer, GLintptr offset, int stride);
		void EnableVertexAttribArray(unsigned int index);
		void VertexArrayElementBuffer(unsigned int buffer);
	};
}