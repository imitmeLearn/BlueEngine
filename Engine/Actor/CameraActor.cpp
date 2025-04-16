#include "CameraActor.h"
#include "Component/CameraComponent.h"
#include "Core/InputController.h"
#include "Core\Engine.h"

namespace Blue
{
CameraActor::CameraActor()
{
	//카메라 컴포넌트 추가
	AddComponent(std::make_shared<CameraComponent>());
}
void CameraActor::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);
	Move(deltaTime);
	Rotate(deltaTime);
}
void CameraActor::Move(float deltaTime)
{
	if(!InputController::IsValid())
	{
		return;
	}
	static InputController& input = InputController::Get();

	//@Test 입력테스트 ('A')
	if(input.IsKeyDown(VK_ESCAPE))
	{
		//팝업 창 띄우기
		if(MessageBox(nullptr
			,TEXT("WANT TO QUIT?")
			,TEXT("QUIT ENGINE")
			,MB_YESNO)==IDYES)
		{
			Engine::Get().Quit();
		}
	}

	//카메라 이동 처리
	if(input.IsKey('A') || input.IsKey(VK_LEFT))
	{
		//왼쪽이동
		transform.position.x -= 1.f*deltaTime;
	}

	if(input.IsKey('D') || input.IsKey(VK_RIGHT))
	{
		//오른쪽이동
		transform.position.x += 1.f*deltaTime;
	}

	if(input.IsKey('W') || input.IsKey(VK_UP))
	{
		//위쪽이동
		transform.position.z += 1.f*deltaTime;
	}

	if(input.IsKey('S') || input.IsKey(VK_DOWN))
	{
		//아래쪽이동
		transform.position.z-= 1.f*deltaTime;
	}

	if(input.IsKey('E'))
	{
		//위쪽이동
		transform.position.y += 1.f*deltaTime;
	}

	if(input.IsKey('Q'))
	{
		//아래쪽이동
		transform.position.y -= 1.f*deltaTime;
	}
}
void CameraActor::Rotate(float deltaTime)
{
	static InputController& input = InputController::Get();

	//마우스 드래그 확인.
	//0->왼쪽버튼 1/2
	if(input.IsButton(0))
	{
		//드래그 감도
		static float sensitivity = 0.05f;

		//카메라
		transform.rotation.x += input.GetMouseDeltaY()*sensitivity;	//상하 회전
		transform.rotation.y += input.GetMouseDeltaX()*sensitivity;	//좌우 회전
	}
}
}