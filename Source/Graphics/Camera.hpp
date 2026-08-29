#pragma once
#include<string>
#include<string_view>
#include<fstream>
#include<nlohmann/json.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"Util/Log.hpp"
namespace SimpleCraft
{
	class Camera
	{
	private:
		float _referenceLeft;
		float _referenceRight;
		float _referenceBottom;
		float _referenceTop;
		float _referenceZNear;
		float _referenceZFar;
		float _left;
		float _right;
		float _bottom;
		float _top;
		glm::vec2 _view;
	public:
		Camera(std::string_view path);
		void Update(int widthWindow, int heightWindow);
		glm::mat4 GetProjection() const;
		void SetView(glm::vec2 view);
		void MoveView(glm::vec2 view);
		glm::vec2 GetView() const;
		float GetReferenceLeft() const;
		float GetReferenceRight() const;
		float GetReferenceBottom() const;
		float GetReferenceTop() const;
		float GetLeft() const;
		float GetRight() const;
		float GetBottom() const;
		float GetTop() const;
		glm::vec2 MouseToWorld(double xpos, double ypos, int widthWindow, int heightWindow) const;
	};
}