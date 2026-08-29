#include"Trigger.hpp"
SimpleCraft::Trigger::Trigger(SimpleCraft::TriggerMode triggerMode) : _state{}, _last{}
{
	_mode = triggerMode;
}
void SimpleCraft::Trigger::Update(bool isPress)
{
	if (_mode == SimpleCraft::TriggerMode::Toggle)
	{
		if (isPress && !_last)
		{
			_state = !_state;
		}
		_last = isPress;
	}
	if (_mode == SimpleCraft::TriggerMode::OnPress)
	{
		if (isPress && !_last)
		{
			_state = true;
		}
		else
		{
			_state = false;
		}
		_last = isPress;
	}
}
bool SimpleCraft::Trigger::GetState() const
{
	return _state;
}