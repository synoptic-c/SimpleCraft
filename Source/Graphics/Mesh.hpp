#pragma once
#include<string>
#include<string_view>
#include<fstream>
#include<nlohmann/json.hpp>
#include<glad/glad.h>
#include"Util/Log.hpp"
#include"VertexArray.hpp"
#include"VertexBuffer.hpp"
#include"IndexBuffer.hpp"
namespace SimpleCraft
{
	class Mesh
	{
	private:
		SimpleCraft::VertexArray _vertexArray;
		SimpleCraft::VertexBuffer _vertexBuffer;
		SimpleCraft::IndexBuffer _indexBuffer;
		int _count;
	public:
		Mesh(std::string_view path);
		void Bind() const;
		void Draw() const;
		int GetCount() const;
	};
}