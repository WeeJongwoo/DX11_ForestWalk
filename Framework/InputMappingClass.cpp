#include "InputMappingClass.h"

InputMappingClass::InputMappingClass() : KeyEvent(256), KeyDownEvent(256), KeyUpEvent(256)
{
}

void InputMappingClass::BindKeyEvent(int KeyIndex, std::function<void()> Function)
{
	if (KeyEvent[KeyIndex])
	{
		return;
	}

	KeyEvent[KeyIndex] = Function;
}

void InputMappingClass::BindKeyDownEvent(int KeyIndex, std::function<void()> Function)
{
	if (KeyDownEvent[KeyIndex])
	{
		return;
	}

	KeyDownEvent[KeyIndex] = Function;
}

void InputMappingClass::BindKeyUpEvent(int KeyIndex, std::function<void()> Function)
{
	if (KeyUpEvent[KeyIndex])
	{
		return;
	}

	KeyUpEvent[KeyIndex] = Function;
}

void InputMappingClass::SetMouseState(float X, float Y)
{
	MouseStateX = X;
	MouseStateY = Y;
}

float InputMappingClass::GetMouseStateX()
{
	return MouseStateX;
}

float InputMappingClass::GetMouseStateY()
{
	return MouseStateY;
}

void InputMappingClass::BindMouseEvent(std::function<void()> Function)
{
	if (MouseMoveEvent)
	{
		return;
	}

	MouseMoveEvent = Function;


}

