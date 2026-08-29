#pragma once
#include<glad/glad.h>
namespace SimpleCraft
{
	class IndexBuffer
	{
	private:
		unsigned int _indexBuffer;
	public:
		IndexBuffer();
		~IndexBuffer();
		IndexBuffer(const SimpleCraft::IndexBuffer&) = delete;
		SimpleCraft::IndexBuffer& operator=(const SimpleCraft::IndexBuffer&) = delete;
		IndexBuffer(SimpleCraft::IndexBuffer&& other) noexcept;
		SimpleCraft::IndexBuffer& operator=(SimpleCraft::IndexBuffer&& other) noexcept;
		unsigned int GetIndexBuffer() const;
		void NamedBufferData(GLsizeiptr size, const void* data, unsigned int usage);
	};
}