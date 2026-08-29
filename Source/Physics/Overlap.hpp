#pragma once
#include<string>
#include<glm/glm.hpp>
#include"Bound.hpp"
namespace SimpleCraft
{
	class Overlap
	{
	private:

	public:
		static bool Check(SimpleCraft::Bound selfBound, SimpleCraft::Bound otherBound, glm::vec2 selfPosition, glm::vec2 otherPosition);
	};
}