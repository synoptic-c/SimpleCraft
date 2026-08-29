#include"Timer.hpp"
SimpleCraft::Timer::Timer() : _currentTime{}, _lastTime {}, _deltaTime{}
{
	_lastTime = (float)glfwGetTime();
}
void SimpleCraft::Timer::Update()
{
	_currentTime = (float)glfwGetTime();
	_deltaTime = _currentTime - _lastTime;
	_lastTime = _currentTime;
	if (_deltaTime > 0.125f)
	{
		_deltaTime = 0.016667f;
	}
}
float SimpleCraft::Timer::GetDeltaTime()
{
	return _deltaTime;
}