#include"Camera.hpp"
SimpleCraft::Camera::Camera(std::string_view path) : _referenceLeft{}, _referenceRight{}, _referenceBottom{}, _referenceTop{}, _left{}, _right{}, _bottom{}, _top{}, _referenceZNear{}, _referenceZFar{}, _view{}
{
	std::fstream file(std::string(path), std::ios::in);
	if (!file)
	{
		PRINT_ERROR_FILE("Failed to open file", path);
		return;
	}
	nlohmann::json cameraJson = nlohmann::json::parse(file);
	file.close();
	_referenceLeft = cameraJson["referenceLeft"].get<float>();
	_referenceRight = cameraJson["referenceRight"].get<float>();
	_referenceBottom = cameraJson["referenceBottom"].get<float>();
	_referenceTop = cameraJson["referenceTop"].get<float>();
	_referenceZNear = cameraJson["referenceZNear"].get<float>();
	_referenceZFar = cameraJson["referenceZFar"].get<float>();
}
void SimpleCraft::Camera::Update(int widthWindow, int heightWindow)
{
	float widthSize = _referenceRight - _referenceLeft;
	float heightSize = _referenceTop - _referenceBottom;
	float ratioWindow = (float)widthWindow / (float)heightWindow;
	float ratioReference = widthSize / heightSize;
	_left = _referenceLeft;
	_right = _referenceRight;
	_bottom = _referenceBottom;
	_top = _referenceTop;
	if (ratioWindow < ratioReference)
	{
		float widthCut = (widthSize - heightSize * ratioWindow) * 0.5f;
		_left = _referenceLeft + widthCut;
		_right = _referenceRight - widthCut;
		return;
	}
	if (ratioWindow > ratioReference)
	{
		float heightCut = (heightSize - widthSize / ratioWindow) * 0.5f;
		_bottom = _referenceBottom + heightCut;
		_top = _referenceTop - heightCut;
		return;
	}
}
glm::mat4 SimpleCraft::Camera::GetProjection() const
{
	return glm::ortho(_left, _right, _bottom, _top, _referenceZNear, _referenceZFar);
}
void SimpleCraft::Camera::SetView(glm::vec2 view)
{
	_view = view;
}
void SimpleCraft::Camera::MoveView(glm::vec2 view)
{
	_view += view;
}
glm::vec2 SimpleCraft::Camera::GetView() const
{
	return _view;
}
float SimpleCraft::Camera::GetReferenceLeft() const
{
	return _referenceLeft;
}
float SimpleCraft::Camera::GetReferenceRight() const
{
	return _referenceRight;
}
float SimpleCraft::Camera::GetReferenceBottom() const
{
	return _referenceBottom;
}
float SimpleCraft::Camera::GetReferenceTop() const
{
	return _referenceTop;
}
float SimpleCraft::Camera::GetLeft() const
{
	return _left;
}
float SimpleCraft::Camera::GetRight() const
{
	return _right;
}
float SimpleCraft::Camera::GetBottom() const
{
	return _bottom;
}
float SimpleCraft::Camera::GetTop() const
{
	return _top;
}
glm::vec2 SimpleCraft::Camera::MouseToWorld(double xpos, double ypos, int widthWindow, int heightWindow) const
{
	return glm::vec2(
		(float)xpos / ((float)widthWindow / (_right - _left)),
		((float)heightWindow - (float)ypos) / ((float)heightWindow / (_top - _bottom))
	);
}