#pragma once
namespace SimpleCraft
{
	enum class TriggerMode
	{
		Toggle,
		OnPress
	};
	class Trigger
	{
	private:
		bool _state;
		bool _last;
		SimpleCraft::TriggerMode _mode;
	public:
		Trigger(SimpleCraft::TriggerMode triggerMode);
		void Update(bool isPress);
		bool GetState() const;
	};
}