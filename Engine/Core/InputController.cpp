#include "InputController.h"

namespace Blue
{
//static 변수 정의.
InputController* InputController::instance = nullptr;

InputController::InputController()
{}
InputController::~InputController()
{}
bool InputController::IsKeyDown(unsigned int keyCode)
{
	return KeyInputData[keyCode].isKeyDown;
}
bool InputController::IsKeyUp(unsigned int keyCode)
{
	return KeyInputData[keyCode].isKeyUp;
}
bool InputController::IsKey(unsigned int keyCode)
{
	return KeyInputData[keyCode].isKey;
}
bool InputController::IsButtonDown(unsigned int Button)
{
	return mouseInputData[Button].isButtonDown;
}
bool InputController::IsButtonUp(unsigned int Button)
{
	return mouseInputData[Button].isButtonUp;
}
bool InputController::IsButton(unsigned int Button)
{
	return mouseInputData[Button].isButton;
}
Vector2 InputController::GetMousePosition()
{
	return Vector2();
}
float InputController::GetMouseDeltaX()
{
	return 0.0f;
}
float InputController::GetMouseDeltaY()
{
	return 0.0f;
}
void InputController::SetKeyUpDown(unsigned int KeyCode,bool isKeyUp,bool isKeyDown)
{}
void InputController::SetButtonUpDown(unsigned int button,bool isButtonUp,bool isButtonDown)
{}
void InputController::SetMousePosition(int x,int y)
{}
InputController & InputController::Get()
{
	return *instance;
}
}