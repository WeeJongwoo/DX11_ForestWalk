#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <queue>
#include <dinput.h>


enum class InputType
{
	Key_Down,
	Key_Held,	
	Key_Up,		
	Mouse_Move	
};


struct InputEvent
{
	InputType Type;
	int       Key = 0;			
	float     MouseX = 0.0f;	
	float     MouseY = 0.0f;	
};


class InputMappingClass
{
	InputMappingClass();
	InputMappingClass(const InputMappingClass&) = delete;
	InputMappingClass operator=(const InputMappingClass&) = delete;
	InputMappingClass(const InputMappingClass&&) = delete;
	InputMappingClass operator=(const InputMappingClass&&) = delete;

	// 키 1개당 핸들러 여러 개를 허용한다(멀티 구독).
	std::vector<std::vector<std::function<void()>>> KeyEvent;
	std::vector<std::vector<std::function<void()>>> KeyDownEvent;
	std::vector<std::vector<std::function<void()>>> KeyUpEvent;

	std::vector<std::function<void()>> MouseMoveEvent;

	float MouseStateX;
	float MouseStateY;

	// 수집(InputClass)과 배포(DispatchQueue)를 분리하는 이벤트 큐.
	std::queue<InputEvent> EventQueue;

public:
	static InputMappingClass& GetInstance()
	{
		static InputMappingClass Instance;
		return Instance;
	}

	// --- 구독(바인딩) ---
	void BindKeyEvent(int KeyIndex, std::function<void()> Function);
	void BindKeyDownEvent(int KeyIndex, std::function<void()> Function);
	void BindKeyUpEvent(int KeyIndex, std::function<void()> Function);
	void BindMouseEvent(std::function<void()> Function);

	// --- 수집: InputClass가 매 프레임 이벤트를 큐에 넣는다 ---
	void QueueEvent(const InputEvent& Event);

	// --- 배포: 프레임당 한 번 큐를 비우며 구독자에게 전달한다 ---
	void DispatchQueue();

	// 마우스 델타 조회(카메라 등 핸들러에서 사용).
	float GetMouseStateX();
	float GetMouseStateY();
};
