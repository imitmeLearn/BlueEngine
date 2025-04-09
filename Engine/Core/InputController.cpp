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
	return keyInputData[keyCode].isKeyDown;
}
bool InputController::IsKeyUp(unsigned int keyCode)
{
	return keyInputData[keyCode].isKeyUp;
}
bool InputController::IsKey(unsigned int keyCode)
{
	return keyInputData[keyCode].isKey;
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
void InputController::ResetInputs()
{
	for(KeyInputData& data:keyInputData)
	{
		data.isKeyUp = false;
		data.isKeyDown = false;
	}

	for(MouseInputData& data : mouseInputData)
	{
		data.isButtonDown = false;
		data.isButtonUp = false;
	}

	mousePreviousPosition = mousePosition;
}
Vector2 InputController::GetMousePosition()
{
	return mousePosition;
}
float InputController::GetMouseDeltaX()
{
	return mousePosition.x - mousePreviousPosition.x;
}
float InputController::GetMouseDeltaY()
{
	return mousePosition.y - mousePreviousPosition.y;
}
void InputController::SetKeyUpDown(unsigned int KeyCode,bool isKeyUp,bool isKeyDown)
{
	keyInputData[KeyCode].SetKeyUpDown(isKeyUp,isKeyDown);
}
void InputController::SetButtonUpDown(unsigned int button,bool isButtonUp,bool isButtonDown)
{
	mouseInputData[button].SetButtonUpDown(isButtonUp,isButtonDown);
}
void InputController::SetMousePosition(int x,int y)
{
	mousePreviousPosition = mousePosition;
	mousePosition = Vector2((float)x,(float)y);
}
InputController & InputController::Get()
{
	return *instance;
}
}