#include"Overlap.hpp"
bool SimpleCraft::Overlap::Check(SimpleCraft::Bound selfBound, SimpleCraft::Bound otherBound, glm::vec2 selfPosition, glm::vec2 otherPosition)
{
	float selfLeft = selfPosition.x - selfBound.left;
	float selfRight = selfPosition.x + selfBound.right;
	float selfBottom = selfPosition.y - selfBound.bottom;
	float selfTop = selfPosition.y + selfBound.top;
	float otherLeft = otherPosition.x - otherBound.left;
	float otherRight = otherPosition.x + otherBound.right;
	float otherBottom = otherPosition.y - otherBound.bottom;
	float otherTop = otherPosition.y + otherBound.top;
	return selfRight > otherLeft && selfLeft < otherRight && selfTop > otherBottom && selfBottom < otherTop;
}