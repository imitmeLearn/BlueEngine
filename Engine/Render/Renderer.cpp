#include "Renderer.h"

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
		MessageBoxA(nullptr,"fail ","ERROR",MB_OK);
	}
}
Renderer::~Renderer()
{}
void Renderer::Draw()
{}
}