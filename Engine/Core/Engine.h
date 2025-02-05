#pragma once

#include <memory> //스마트포인터
#include <Windows.h>
#include <string>
#include "Type.h"

namespace Blue
{
class Engine	//엔진클래스, 어플리케이션 레벨에서, 엔진 단 기능 창구, 기본적으로 전체 리소스를 관리하도록 제작
{
public:
	Engine(uint32 width,uint32 height,const std::wstring& title,HINSTANCE hInstance);
	virtual	~Engine();

	//엔진 실행 함수
	void Run ();

	//윈도우 메시지 루프 처리
	static LRESULT CALLBACK WindowProc(HWND handle,UINT message,WPARAM wparam,LPARAM lparam);

	static Engine& Get();
protected:

	std::shared_ptr<class Window> window;		//창 객체
	std::shared_ptr<class Renderer> renderer;	//렌더러 객체
	static Engine* instance;					//싱글톤 객체

private:
};
}