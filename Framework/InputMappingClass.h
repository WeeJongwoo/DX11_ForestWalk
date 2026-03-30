#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <dinput.h>


class InputMappingClass
{
	InputMappingClass();
	InputMappingClass(const InputMappingClass&) = delete;
	InputMappingClass operator=(const InputMappingClass&) = delete;
	InputMappingClass(const InputMappingClass&&) = delete;
	InputMappingClass operator=(const InputMappingClass&&) = delete;

	std::vector<std::function<void()>> KeyEvent;
	std::vector<std::function<void()>> KeyDownEvent;
	std::vector<std::function<void()>> KeyUpEvent;

	float MouseStateX;
	float MouseStateY;

	std::function<void()> MouseMoveEvent;

public:
	static InputMappingClass& GetInstance()
	{
		static InputMappingClass Instance;
		return Instance;
	}

	const std::vector<std::function<void()>>& GetKeyEvent()
	{
		return KeyEvent;
	}

	const std::vector<std::function<void()>>& GetKeyDownEvent()
	{
		return KeyDownEvent;
	}

	const std::vector<std::function<void()>>& GetKeyUpEvent()
	{
		return KeyUpEvent;
	}

	const std::function<void()>& GetMouseMoveEvent()
	{
		return MouseMoveEvent;
	}

	void BindKeyEvent(int KeyIndex, std::function<void()> Function);
	void BindKeyDownEvent(int KeyIndex, std::function<void()> Function);
	void BindKeyUpEvent(int KeyIndex, std::function<void()> Function);

	void SetMouseState(float X, float Y);
	float GetMouseStateX();
	float GetMouseStateY();
	void BindMouseEvent(std::function<void()> Function);
};

