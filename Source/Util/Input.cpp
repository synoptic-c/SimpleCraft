#include"Input.hpp"
SimpleCraft::Input::Input() : _left{}, _right{}, _down{}, _up{}, _slots{}, _attackDestroy{}, _usePlace{}, _isInventory{ SimpleCraft::TriggerMode::Toggle }, _mouseWorld{}, _clickLeft{ SimpleCraft::TriggerMode::OnPress }, _clickRight{ SimpleCraft::TriggerMode::OnPress }
{
	_slotkeys = {
		GLFW_KEY_1,
		GLFW_KEY_2,
		GLFW_KEY_3,
		GLFW_KEY_4,
		GLFW_KEY_5,
		GLFW_KEY_6,
		GLFW_KEY_7,
		GLFW_KEY_8,
		GLFW_KEY_9,
	};
	_slots.reserve(_slotkeys.size());
	for (unsigned int i = 0; i < _slotkeys.size(); i++)
	{
		_slots.emplace_back(bool{});
	}
}
void SimpleCraft::Input::Update(const SimpleCraft::Window& window, const SimpleCraft::Camera& camera)
{
	_left = window.GetKey(GLFW_KEY_A);
	_right = window.GetKey(GLFW_KEY_D);
	_down = window.GetKey(GLFW_KEY_LEFT_SHIFT);
	_up = window.GetKey(GLFW_KEY_SPACE);
	_clickLeft.Update(window.GetMouseButton(GLFW_MOUSE_BUTTON_LEFT));
	_clickRight.Update(window.GetMouseButton(GLFW_MOUSE_BUTTON_RIGHT));
	_attackDestroy = window.GetMouseButton(GLFW_MOUSE_BUTTON_LEFT);
	_usePlace = window.GetMouseButton(GLFW_MOUSE_BUTTON_RIGHT);
	for (unsigned int i = 0; i < _slotkeys.size(); i++)
	{
		_slots[i] = window.GetKey(_slotkeys[i]);
	}
	_isInventory.Update(window.GetKey(GLFW_KEY_TAB));
	_mouseWorld = camera.MouseToWorld(window.GetCursorPosX(), window.GetCursorPosY(), window.GetFramebufferSizeX(), window.GetFramebufferSizeY());
}
bool SimpleCraft::Input::GetLeft() const
{
	return _left;
}
bool SimpleCraft::Input::GetRight() const
{
	return _right;
}
bool SimpleCraft::Input::GetDown() const
{
	return _down;
}
bool SimpleCraft::Input::GetUp() const
{
	return _up;
}
bool SimpleCraft::Input::GetAttackDestroy() const
{
	return _attackDestroy;
}
bool SimpleCraft::Input::GetUsePlace() const
{
	return _usePlace;
}
bool SimpleCraft::Input::GetClickLeft() const
{
	return _clickLeft.GetState();
}
bool SimpleCraft::Input::GetClickRight() const
{
	return _clickRight.GetState();
}
const std::vector<unsigned char>& SimpleCraft::Input::GetSlots() const
{
	return _slots;
}
bool SimpleCraft::Input::GetIsInventory() const
{
	return _isInventory.GetState();
}
glm::vec2 SimpleCraft::Input::GetMouseWorld() const
{
	return _mouseWorld;
}