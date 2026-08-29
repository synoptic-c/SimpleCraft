#pragma once
#include<vector>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include"Util/Trigger.hpp"
#include"Graphics/Window.hpp"
#include"Graphics/Camera.hpp"
namespace SimpleCraft
{
	class Input
	{
	private:
		bool _left;
		bool _right;
		bool _down;
		bool _up;
		bool _attackDestroy;
		bool _usePlace;
		SimpleCraft::Trigger _clickLeft;
		SimpleCraft::Trigger _clickRight;
		std::vector<unsigned char> _slots;
		std::vector<int> _slotkeys;
		SimpleCraft::Trigger _isInventory;
		glm::vec2 _mouseWorld;
	public:
		Input();
		void Update(const SimpleCraft::Window& window, const SimpleCraft::Camera& camera);
		bool GetLeft() const;
		bool GetRight() const;
		bool GetDown() const;
		bool GetUp() const;
		bool GetAttackDestroy() const;
		bool GetUsePlace() const;
		bool GetClickLeft() const;
		bool GetClickRight() const;
		const std::vector<unsigned char>& GetSlots() const;
		bool GetIsInventory() const;
		glm::vec2 GetMouseWorld() const;
	};
}