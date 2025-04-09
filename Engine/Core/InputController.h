#pragma once
#include "Math/Vector2.h"

//입력처리를 담당하는 클래스
namespace Blue{
//키 입력 처리를 위한 구조체
struct KeyInputData
{
	////입력관련 변수 -> 비트로 하는방법도 있고, 캐릭터로도 가능하고, 플래그로도 가능하고, 고민해보기. 지금은 bool로함.
	bool isKeyDown = false;
	bool isKeyUp = false;
	bool isKey = false;

	//키값 설정 함수
	void SetKeyUpDown(bool isKeyUp,bool isKeyDown)
	{
		this->isKeyUp = isKeyUp;
		this->isKeyDown = isKeyDown;

		isKey = isKeyDown && !isKeyUp;
	}
};
//마우스 입력 처리를 위한 구조체
struct MouseInputData
{
	bool isButtonDown = false;
	bool isButtonUp = false;
	bool isButton = false;

	void SetButtonUpDown(bool isButtonUp,bool isButtonDown)
	{
		this->isButtonUp = isButtonUp;
		this->isButtonDown = isButtonDown;

		isButton = isButtonDown && !isButtonUp;
	}
};

//입력 관리자 클래스
class InputController
{
public:
	InputController();
	~InputController();

	////편의함수
	////KeyCode -> 버튼 값 (예: 'A').
	bool IsKeyDown (unsigned int keyCode);
	bool IsKeyUp (unsigned int keyCode);
	bool IsKey (unsigned int keyCode);

	////마우스 입력 관련 함수
	bool IsButtonDown (unsigned int Button);
	bool IsButtonUp (unsigned int Button);
	bool IsButton (unsigned int Button);

	//입력정리함수
	void ResetInputs();

	Vector2 GetMousePosition();
	float GetMouseDeltaX();	//이전 프레임 대비 이동한 거리 X
	float GetMouseDeltaY();	//이전 프레임 대비 이동한 거리 Y

	//설정함수 - 콜백함수 통해서,  한번에 처리
	void SetKeyUpDown(unsigned int KeyCode,bool isKeyUp,bool isKeyDown);
	void SetButtonUpDown(unsigned int button,bool isButtonUp,bool isButtonDown);
	void SetMousePosition(int x,int y);

	static	InputController& Get();	//싱글톤 접근 함수.//구조 명확하지 않으면, 안정성 확보 안됨.

private:

	KeyInputData keyInputData[256];//키 입력 관련 변수 //256 개면, 대부분 만들 수 있다. 넉넉함
	MouseInputData mouseInputData[3];//버튼 입력 관련 변수 / 좌-우-휠

	////마우스 위치 변수
	Vector2 mousePosition = Vector2::Zero;
	Vector2 mousePreviousPosition = Vector2::Zero;
	static InputController* instance;	//싱글톤(Singleton) 구현을 위한 변수
};
}
