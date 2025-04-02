#include "Engine.h"

#include "../Render/Renderer.h"
#include "Window.h"

#include "Resource\ShaderLoader.h"
#include "Resource\TextureLoader.h"
#include "Resource\ModelLoader.h"
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
				std::cout <<"DeltaTime : "<< deltaTime
					<<"| OneFrameTime : "<<oneframeTime
					<<"| FPS : "<<(1.f/deltaTime)
					<<"| FPS(int) : "<<(int)(1.f/deltaTime)
					<<"| FPS(int)ceil : "<<(int)ceil(1.f/deltaTime) //소수점 안나오게하려고
					<<"\n";

				//엔진 루프

				//레벨 처리
				if(mainLevel)
				{
					mainLevel->BeginPlay();
					mainLevel->Tick(1.f/60.f);
					renderer->Draw(mainLevel);
				}

				previousTime = currentTime;	//프레임 시간 업데이트
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
	switch(message)
	{
		//창이 삭제되면 ,실행
	case WM_DESTROY:
	PostQuitMessage(0);	//프로그램 종료 메시지 발행.
	return 0;

	default:
	break;
	}
	return DefWindowProc(handle,message,wparam,lparam);	 //윈도우가 제공하는 함수	//기본 메세지처리
}

Engine& Engine::Get()
{
	return *instance;
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