#pragma once
#include<glad/glad.h>
namespace SimpleCraft
{
	class VertexBuffer
	{
	private:
		unsigned int _vertexBuffer;
	public:
		VertexBuffer();
		~VertexBuffer();
		VertexBuffer(const SimpleCraft::VertexBuffer&) = delete;
		SimpleCraft::VertexBuffer& operator=(const SimpleCraft::VertexBuffer&) = delete;
		VertexBuffer(SimpleCraft::VertexBuffer&& other) noexcept;
		SimpleCraft::VertexBuffer& operator=(SimpleCraft::VertexBuffer&& other) noexcept;
		unsigned int GetVertexBuffer() const;
		void NamedBufferData(GLsizeiptr size, const void* data, unsigned int usage);
	};
}