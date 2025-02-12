#include "Engine.h"

#include "../Render/Renderer.h"
#include "Window.h"
namespace Blue
{
Engine* Engine:: instance = nullptr;	//싱글통 객체 설정
Engine::Engine(uint32 width,uint32 height,const std::wstring& title,HINSTANCE hInstance)	// const std::wstring& //임시값 참조로 하려면 const 붙이기! cpp 규약에 나옴. ->https://learn.microsoft.com/ko-kr/cpp/cpp/reference-type-function-arguments?view=msvc-170
{
	instance = this;	//싱글톤 객체 값 설정.
	window = std::make_shared<Window>(width,height,title,hInstance,WindowProc);	//창 객체 생성
	renderer= std::make_shared<Renderer>(width,height,window->Handle());	//렌더 객체 생성
}
Engine::~Engine()
{}
void Engine::Run()
{
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
			//엔진 루프
			renderer->Draw();
		}
	}
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