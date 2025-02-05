#include "Renderer.h"
#include <vector>
namespace 	Blue
{
Renderer::Renderer(uint32 width,uint32 height,HWND window)
{
	uint32 flag = 0u;		//장치 생성에 사용하는 옵션.

	#if _DEBUG
	flag |= D3D11_CREATE_DEVICE_DEBUG;
	#endif
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1		//얘 시도하고
		,D3D_FEATURE_LEVEL_11_0		//안되면, 얘 시도하고 ...
	};
	//스왑 체인 정보 구조체
	//typedef struct DXGI_SWAP_CHAIN_DESC
	//{
	//	DXGI_MODE_DESC BufferDesc;
	//	DXGI_SAMPLE_DESC SampleDesc;
	//	DXGI_USAGE BufferUsage;
	//	UINT BufferCount;
	//	HWND OutputWindow;
	//	BOOL Windowed;
	//	DXGI_SWAP_EFFECT SwapEffect;
	//	UINT Flags;
	//}

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};	//주소값 보낼거야
	swapChainDesc.Windowed = true;				//창모드?
	swapChainDesc.OutputWindow = window;
	swapChainDesc.BufferUsage= DXGI_USAGE_RENDER_TARGET_OUTPUT;	//사용목적 지정
	swapChainDesc.BufferCount =1;			//백버퍼 개수.
	swapChainDesc.SampleDesc.Count =1;		//멀티 샘플링 개수.	//1개한다는건, 안쓰겠다는 거임
	swapChainDesc.SampleDesc.Quality=0;		//멀티 샘플링 수준.
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//RGB unNormal?
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;	//0,1 주로 사용한다 하드웨어 빨라서, 1해도 잘 나온데, 예전엔 잔상남았엇따?

	//D3D_FEATURE_LEVEL targetLevel;

	//장치 생성
	HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr,D3D_DRIVER_TYPE_HARDWARE,nullptr
		,flag,featureLevels,_countof(featureLevels),D3D11_SDK_VERSION,&swapChainDesc
		,&swapChain,&device,nullptr/*targetLevel*/,&context);

	//결과 확인
	if(FAILED(result))
	{
		MessageBoxA(nullptr,"fail to D3D11CreateDeviceAndSwapChain ","ERROR",MB_OK);
		__debugbreak();
	}

	//이미지 그리는 대상 (=렌더타겟) 뷰 생성 : 크기는 창 크기와 같아야 한다.
	ID3D11Texture2D* backbuffer = nullptr; //받아올려고, 포인터타입으로...

	result =swapChain -> GetBuffer(0,IID_PPV_ARGS(&backbuffer));	//ㄴ 메크로! <- //swapChain -> GetBuffer(0,__uuidof(backbuffer),reinterpret_cast<void**> (&backbuffer));

	if(FAILED(result))//결과 확인
	{
		MessageBoxA(nullptr,"fail to get back buffer ","ERROR",MB_OK);
		__debugbreak();
	}

	result=	device -> CreateRenderTargetView(backbuffer,nullptr,&renderTargetView);

	if(FAILED(result))	//결과 확인
	{
		MessageBoxA(nullptr,"fail to CreateRenderTargetView  ","ERROR",MB_OK);
		__debugbreak();
	}

	//렌더 타겟 뷰 바인딩(연결)
	context -> OMSetRenderTargets(1,&renderTargetView,nullptr);

	//뷰 포트(화면)
	viewport.TopLeftX = 0.f;
	viewport.TopLeftY = 0.f;
	viewport.Width = (float)width;
	viewport.Height= (float)height;
	viewport.MaxDepth = 1.f;
	viewport.MinDepth= 0.f;

	//퓨 포트 설정
	context -> RSSetViewports(1,&viewport);

	//정점 데이터 생성
	float vertices[] =
	{
		//화면 기본 좌표,
		0.f,0.5f,0.5f
		,0.5f,-0.5f,0.5f
		,-0.5f,-0.5f,0.5f
	};

	//@Temp 임시 리소스 생성 - 버텍스
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.ByteWidth = sizeof(float) *3 *3;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; //필수

	D3D11_SUBRESOURCE_DATA vertexData = {};	//정점 데이터 //여러데이터, 하나로 넣을 떄 사용
	vertexData.pSysMem =	vertices;

	result= device -> CreateBuffer(&vertexBufferDesc,&vertexData,&vertexBuffer);		//버퍼(Buffer) 메모리 덩어리 - 버텍스
	if(FAILED(result))	//결과 확인
	{
		MessageBoxA(nullptr,"fail to CreateBuffer - vertex  ","ERROR",MB_OK);
		__debugbreak();
	}

	//인덱스 (색인) 버퍼 생성 (정점을 조립하는 순서)
	int indeice[] =
	{
		0,1,2
	};

	//@Temp 임시 리소스 생성 - 인덱스
	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.ByteWidth = sizeof(int)  *3;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER; //필수

	D3D11_SUBRESOURCE_DATA indexData = {};	//정점 데이터 //여러데이터, 하나로 넣을 떄 사용
	indexData.pSysMem =	indeice;

	result=	device -> CreateBuffer(&indexBufferDesc,&indexData,&indexBuffer);	//버퍼(Buffer) 메모리 덩어리  - 인덱스
	if(FAILED(result))	//결과 확인
	{
		MessageBoxA(nullptr,"fail to CreateBuffer -index ","ERROR",MB_OK);
		__debugbreak();
	}
	//쉐이더 컴파일,
	//쉐이더 생성/

	//입력 레이아웃, //정점 쉐이더에 전달할 정점 데이터가 어떻게 생겼는지 알려줌.

	//device->CreateInputLayout();
}
Renderer::~Renderer()
{}
void Renderer::Draw()
{
	//그리기 전 작업
	// 	   # 지우기
	//float color[] = {.6f,.7f,.8f,1.f};
	float color[] = {.7f,.8f,.95f,1.f};
	context->ClearRenderTargetView(renderTargetView,color);
	//드로우

	//버퍼교환 -모니터 싱글

	swapChain->Present(1u,0u);
}
}