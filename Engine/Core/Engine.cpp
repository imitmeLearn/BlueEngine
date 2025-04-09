#include "Engine.h"

#include "../Render/Renderer.h"
#include "Window.h"

#include "Resource\ShaderLoader.h"
#include "Resource\TextureLoader.h"
#include "Resource\ModelLoader.h"

#include "inputController.h"
#include "Level/Level.h"

#include <iostream>	//std::cout  출력 사용하려고 추가
namespace Blue
{
Engine* Engine:: instance = nullptr;	//싱글통 객체 설정
Engine::Engine(uint32 width,uint32 height,const std::wstring& title,HINSTANCE hInstance)	// const std::wstring& //임시값 참조로 하려면 const 붙이기! cpp 규약에 나옴. ->https://learn.microsoft.com/ko-kr/cpp/cpp/reference-type-function-arguments?view=msvc-170
{
	instance = this;	//싱글톤 객체 값 설정.
	window = std::make_shared<Window>(width,height,title,hInstance,WindowProc);	//창 객체 생성
	shaderLoader = std::make_unique<ShaderLoader>();		//셰이더 로더 객체 생성
	textureLoader = std::make_unique<TextureLoader>();		//셰이더 로더 객체 생성
	modelLoader = std::make_unique<ModelLoader>();			//모델 로더 객체 생성
	inputController = std::make_unique<InputController>();	//입력 관리자 객체 생성.

	renderer= std::make_shared<Renderer>(width,height,window->Handle());	//렌더 객체 생성
}
Engine::~Engine()
{}
void Engine::Run()
{
	//타이머 (틱/델타타임.
	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;
	LARGE_INTEGER frequency;

	QueryPerformanceFrequency(&frequency);	//하드웨어 타이머의 해상도 값(기준단위)
	QueryPerformanceCounter(&currentTime);	//현재시간
	previousTime = currentTime;
	float targetFrameRate = 120.f;	//프레임 계산에 사용할 변수
	float oneframeTime = 1.f / targetFrameRate;	//고정 프레임 속도를 사용하기 위한 변수.

	//메시지 처리 루프
	MSG msg = {};
	//while(msg.message != WM_DESTROY)
	while(msg.message != WM_QUIT)		//지우고 바꾸고??
	{
		//엔진 종료 처리.
		if(isQuit)
		{
			break;
		}

		//창에 메시지가 들어올 때 실행.
		if(PeekMessage(&msg,nullptr,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);	//메시지 번역.
			DispatchMessage(&msg);	//메시지 전달.
		}
		//창에 메시지가 없을 때 다른 작업 처리
		else
		{
			QueryPerformanceCounter(&currentTime);	//현재시간
			//프레임 시간 계산
			float deltaTime = (float)(currentTime.QuadPart - previousTime.QuadPart)
				/ (float)frequency.QuadPart;

			if(deltaTime >= oneframeTime) //if안하면, 엄청많이 호출되기에, 너중에 컴 터짐.
			{
				//출력
				//std::cout <<"DeltaTime : "<< deltaTime
				//	<<"| OneFrameTime : "<<oneframeTime
				//	<<"| FPS : "<<(1.f/deltaTime)
				//	<<"| FPS(int) : "<<(int)(1.f/deltaTime)
				//	<<"| FPS(int)ceil : "<<(int)ceil(1.f/deltaTime) //소수점 안나오게하려고
				//	<<"\n";

				wchar_t stat[512] = {};	//문자열 생성.
				swprintf_s(stat,512,
					TEXT("[%s] - [DeltaTime: %f] [FPS:%d]")
					,window->Title().c_str()
					,deltaTime
					,(int)ceil(1.f/deltaTime)
				);

				////창 제목에 출력
				SetWindowText(window->Handle(),stat);

				//엔진 루프

				//레벨 처리
				if(mainLevel)
				{
					mainLevel->BeginPlay();
					mainLevel->Tick(1.f/60.f);
					renderer->Draw(mainLevel);
				}

				previousTime = currentTime;	//프레임 시간 업데이트

				inputController->ResetInputs(); //입력 초기화
			}		//플레임 제한
		}
	}
}

//메일레밸 설정
void Engine::SetLevel(std::shared_ptr<class Level> newLevel)
{
	mainLevel = newLevel;
}

//창에 관련된 메시지를 처리하는 콜백
LRESULT Engine::WindowProc(HWND handle,UINT message,WPARAM wparam,LPARAM lparam)
{
	//입력 관리자가 준비 안됐으면, 종료
	if(!InputController::IsValid())
	{
		return DefWindowProc(handle,message,wparam,lparam);	//메시지를 가로채서, 명시적으로 처리 하지 않으면, 문제생기기에, 넣어줌.
	}

	switch(message)
	{
		//창이 삭제되면 ,실행
	case WM_DESTROY:
	//PostQuitMessage(0);	//프로그램 종료 메시지 발행.
	Engine::Get().Quit();
	break;

	//윈도우 메시제 _ 왼쪽버튼 눌렸음.
	case WM_LBUTTONDOWN:
	{
		InputController::Get().SetButtonUpDown(0,false,true);
	}
	break;

	case WM_LBUTTONUP:
	{
		InputController::Get().SetButtonUpDown(0,true,false);
	}
	break;

	case WM_RBUTTONDOWN:
	{
		InputController::Get().SetButtonUpDown(1,false,true);
	}
	break;

	case WM_RBUTTONUP:
	{
		InputController::Get().SetButtonUpDown(1,true,false);
	}
	break;

	case WM_MBUTTONDOWN:
	{
		InputController::Get().SetButtonUpDown(2,false,true);
	}
	break;

	case WM_MBUTTONUP:
	{
		InputController::Get().SetButtonUpDown(2,true,false);
	}
	break;

	case WM_MOUSEMOVE:
	{
		//현재 마우스 포인터 위치 값 가져오기 - msdn WM_MOUSEMOVE 검색하면, 읽는 방법 나옴 :  https://learn.microsoft.com/ko-kr/windows/win32/inputdev/wm-mousemove
		int xPosition = LOWORD(lparam);
		int yPosition = HIWORD(lparam);

		InputController::Get().SetMousePosition(xPosition,yPosition);
	}
	break;

	case WM_SIZE:
	{
		if(wparam == SIZE_MINIMIZED)
		{
			break;
		}

		uint32 width = static_cast<uint32>(LOWORD(lparam));
		uint32 height = static_cast<uint32>(HIWORD(lparam));

		// 가로 / 세로 크기 값 전달.
		Engine::Get().OnResize(width,height); //연결
	}
	break;

	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_KEYDOWN:
	case WM_KEYUP:
	{
		// MSDN 문서를 확인해 보면, 30번째 비트는 KeyUp 상태를 나타낸다고 나옴.
		bool isKeyUp = ((lparam & (static_cast<long long>(1) << 30)) != 0);

		// MSDN 문서를 확인해 보면, 31번째 비트는 KeyDown 상태를 나타낸다고 나옴.
		bool isKeyDown = ((lparam & (static_cast<long long>(1) << 31)) == 0);

		// 엔진에 키 입력 데이터 전달.
		if(isKeyUp != isKeyDown)
		{
			// 가상 키 값.
			uint32 vkCode = static_cast<uint32>(wparam);
			InputController::Get().SetKeyUpDown(vkCode,isKeyUp,isKeyDown);
		}
	} break;

	default:
	break;
	}
	return DefWindowProc(handle,message,wparam,lparam);	 //윈도우가 제공하는 함수	//기본 메세지처리
}

Engine& Engine::Get()
{
	return *instance;
}
void Engine::OnResize(uint32 width,uint32 height)
{
	//예외처리.
	if(!window)
	{
		return;
	}

	if(!renderer)
	{
		return;
	}

	//안전하게 //전체 창 크기에서 실제로 그려지는 영역의 크기를 구하기! ClientRect
	RECT rect;
	GetClientRect(window->Handle(),&rect);

	uint32 w = (uint32)(rect.right - rect.left);
	uint32 h = (uint32)(rect.bottom - rect.top);

	//렌더러 크기 조절 함수 호출
	renderer->OnResize(w,h);
}
void Engine::Quit()
{
	isQuit = true;
}
ID3D11Device& Engine::Device() const
{
	return *renderer->device;
}
ID3D11DeviceContext& Engine::Context() const
{
	return *renderer->context;
}
}