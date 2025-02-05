#include<Windows.h>
#include<winerror.h>

/*
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);	//원본
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);	//가능//사용하는거
LRESULT  WindowProc(HWND, UINT, WPARAM, LPARAM);		//가능
*/

//창에 관련된 메시지를 처리하는 콜백
LRESULT CALLBACK WindowProc(HWND handle,UINT message,WPARAM wparam,LPARAM lparam)	//가능//사용하는거
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

//WINAPI는 define 이야, stdcall cdecl(함수호출규약) 있는데, 스택에 올라갈때, 스택 어떻게 쓸지 규약이 있어.크게 나누면, 사용자 함수랑 시스템 함수 있어 스택잡히는것이 피라미터 잡히는거 반대야
//시스템함수이기에, 앞에 붙여주는거야, 안붙이면, 기본값을 붙여, stdcall, 안붙이면, cdecl 사용자함수로,
//_In_opt_  _In_ 는 안붙여도 되지만, 때고나서 빌드하면, 초록줄로 경고(주석일치않는다고....) 있을거야!옵션처리값이다.붙여도 안붙여도 되긴하다.기억안나면, msdn winmain 검색해서, 보면돼,
//stdcall clrcall 같은거야.한바이트
/*
LPSTR 가보면, char* 야, 해서, LPSTR 대신  char* 써도 된다. 왜 LPSTR냐면, 옛날에? 대문자로 변수할거야 했었기에, Long? Pointer STring 야.

HINSTANCE 는
DECLARE_HANDLE

hInstance는 WinMain 는 창 제어 포인터, 창은, 윈도우즈 운영체제 입장에서 소중한 리소스, 시스템이 관리하는, 생성 부탁하고 제어 메모리르 받는데, 그게, H Instance 야. 프로그램 메모리 주소 생성해서, hInstance에 넣어줌.
hPrevInstance 는 안쓴지 오래됨, 3.1 버전?? 95, 98
_In_ LPSTR lpCmdLine,는
창모드 끌 때, 옵션값이다. 실행할땐 안써. command 에서 실행할 일 없기에,

과장해서 말하면, WinMain은 hInstance 하나 쓰려고 쓰는거야!!!!!!!!!

'msdn 창 만들기' 검색하면,https://learn.microsoft.com/ko-kr/windows/win32/learnwin32/creating-a-window
WNDClass 만들어서, 창 생성하는거 나오는데,. 복사해
*/

//창 모드로 할 때 메인 함수(Entry Point)
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	// Register the window class.
	//창에 사용할 클래스 이름
	//const wchar_t CLASS_NAME[] = L"Sample Window Class"; //원본
	const wchar_t* className = TEXT("Sample Window Class");	//창에 사용할 클래스 이름 //배열대신, 포인터 사용해도 됨.
	//L TEXT  같은거, 메크로야! 타고 들어가면, 유니코드 설정되었을떄 L##quote

	//  = { }; // 기본값 넣어주는거 //좋은 습관, 구조체 엄청만들어서, 기본값 넘기고 하는 것을 많이하게 될것임.
	WNDCLASS wc = {};		//창 생성에 필요한 설정 구조체.

	wc.lpfnWndProc = WindowProc; 	//메세지 처리를 위한 콜백 전달.
	wc.hInstance = hInstance; //프로그램 주소 전달.
	wc.lpszClassName = className; //창 생성에 사용할 클래스 이름 전달.	//필수!!!!

	if(!RegisterClass(&wc))
	{
		auto error = GetLastError();	 //오류메세지 확인

		OutputDebugStringA("Fail to register a window class \n");
		MessageBoxA(nullptr,"Fail to register a window ","Error",MB_OK);

		__debugbreak();
	}
	//else
	//{
	//	//메세지 출력 //std::cout 못써...  //콜솔 아닌 창 환경으로 바뀌었기에직접 만들어서 써야해.
	//	//메세지 출력 #1 - 출력창 (output) 이용.
	//	OutputDebugStringA("창 등록 잘 됨 \n");

	//	//메세지 출력 #2 - 메세지박스 이용.
	//	MessageBoxA(nullptr, "창 생성 잘됨", "택스트 메세지", MB_OK);

	//	//__debugbreak();
	//}

	//창 크기
	unsigned int width = 1280;
	unsigned int height = 800;
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
	HWND hwnd = CreateWindow(

		className,                     // Window class
		TEXT("Blue Engine Demo"),    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		//CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		//positionX,positionY,width,height,
		positionX,positionY,windowWidth,windowHeight,

		nullptr,       // Parent window
		nullptr,       // Menu
		hInstance,  // Instance handle
		nullptr        // Additional application data
	);

	if(hwnd == NULL)
	{
		OutputDebugStringA("Fail to create a window class \n");
		MessageBoxA(nullptr,"Fail to create a window ","Error",MB_OK);

		__debugbreak();
	}

	//창 보이기.
	ShowWindow(hwnd,SW_SHOW);

	//창 메세지 업데이트.
	UpdateWindow(hwnd);

	//메시지 처리 루프
	MSG msg = {};
	//while(msg.message != WM_DESTROY)
	while(msg.message != WM_QUIT)
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
		}
	}

	return 0;
}