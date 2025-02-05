#include "Window.h"

namespace Blue
{
Window::Window(uint32 width,uint32 height,const std::wstring & title,HINSTANCE instance,WNDPROC messageProcedure)
	:width(width),height(height),title(title),instance(instance)
{
	WNDCLASS wc = {};		//창 생성에 필요한 설정 구조체.

	wc.lpfnWndProc = messageProcedure; 	//메세지 처리를 위한 콜백 전달.
	wc.hInstance = instance; //프로그램 주소 전달.
	wc.lpszClassName = className.c_str(); //창 생성에 사용할 클래스 이름 전달.	//필수!!!!

	if(!RegisterClass(&wc))
	{
		auto error = GetLastError();	 //오류메세지 확인

		OutputDebugStringA("Fail to register a window class \n");
		MessageBoxA(nullptr,"Fail to register a window ","Error",MB_OK);

		__debugbreak();
	}

	//화면 가운데 위치 설정
	unsigned int positionX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
	unsigned int positionY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

	//창　크기 조정 - 방법1  // 방법2 : GetClientRect
	RECT rect = {0,0,(long)width,(long)height};
	AdjustWindowRect(&rect,WS_OVERLAPPEDWINDOW,FALSE);

	//창 크기 재설정
	unsigned int windowWidth = rect.right - rect.left;
	unsigned int windowHeight = rect.bottom - rect.top;

	//생성
	handle = CreateWindow(

		className.c_str(),		// Window class
		title.c_str(),			// Window text
		WS_OVERLAPPEDWINDOW,	// Window style

		// Size and position
		//CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		positionX,positionY,windowWidth,windowHeight,

		nullptr,       // Parent window
		nullptr,       // Menu
		instance,  // Instance handle
		nullptr        // Additional application data
	);

	if(handle == NULL)
	{
		OutputDebugStringA("Fail to create a window class \n");
		MessageBoxA(nullptr,"Fail to create a window ","Error",MB_OK);

		__debugbreak();
	}

	//창 보이기.
	ShowWindow(handle,SW_SHOW);

	//창 메세지 업데이트.
	UpdateWindow(handle);
}
Window::~Window()
{
	UnregisterClass(className.c_str(),instance);	//클래스 등록 해제	//안 넣어도 괜찮지만, 정석이다.
}
void Window::SetWidhHeight(uint32 width,uint32 height)
{}
}