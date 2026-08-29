#pragma once
#include<GLFW/glfw3.h>
namespace SimpleCraft
{
	class Timer
	{
	private:
		float _currentTime;
		float _deltaTime;
		float _lastTime;
	public:
		Timer();
		void Update();
		float GetDeltaTime();
	};
}