#include "InputMappingClass.h"

InputMappingClass::InputMappingClass()
	: KeyEvent(256), KeyDownEvent(256), KeyUpEvent(256)
	, MouseStateX(0.0f), MouseStateY(0.0f)
{
}

void InputMappingClass::BindKeyEvent(int KeyIndex, std::function<void()> Function)
{
	KeyEvent[KeyIndex].push_back(std::move(Function));
}

void InputMappingClass::BindKeyDownEvent(int KeyIndex, std::function<void()> Function)
{
	KeyDownEvent[KeyIndex].push_back(std::move(Function));
}

void InputMappingClass::BindKeyUpEvent(int KeyIndex, std::function<void()> Function)
{
	KeyUpEvent[KeyIndex].push_back(std::move(Function));
}

void InputMappingClass::BindMouseEvent(std::function<void()> Function)
{
	MouseMoveEvent.push_back(std::move(Function));
}

void InputMappingClass::QueueEvent(const InputEvent& Event)
{
	EventQueue.push(Event);
}

void InputMappingClass::DispatchQueue()
{
	while (!EventQueue.empty())
	{
		const InputEvent Event = EventQueue.front();
		EventQueue.pop();

		switch (Event.Type)
		{
			case InputType::Key_Down:
			{
				for (const auto& Handler : KeyDownEvent[Event.Key])
				{
					if (Handler) Handler();
				}
				break;
			}

			case InputType::Key_Held:
			{
				for (const auto& Handler : KeyEvent[Event.Key])
				{
					if (Handler) Handler();
				}
				break;
			}

			case InputType::Key_Up:
			{
				for (const auto& Handler : KeyUpEvent[Event.Key])
				{
					if (Handler) Handler();
				}
				break;
			}

			case InputType::Mouse_Move:
			{
				MouseStateX = Event.MouseX;
				MouseStateY = Event.MouseY;

				for (const auto& Handler : MouseMoveEvent)
				{
					if (Handler) Handler();
				}
				break;
			}

			default:
				break;
		}
	}
}

float InputMappingClass::GetMouseStateX()
{
	return MouseStateX;
}

float InputMappingClass::GetMouseStateY()
{
	return MouseStateY;
}
