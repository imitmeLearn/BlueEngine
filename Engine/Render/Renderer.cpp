#include "Renderer.h"
#include <vector>
#include <d3dcompiler.h>
#include"../Math/Vector3.h"
#include "../Shader/Shader.h"
#include "TriangleMesh.h"
#include "QuadMesh.h"
#include <Core\Common.h>
#include "Level/Level.h"
#include "Actor\Actor.h"

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

	D3D_FEATURE_LEVEL outFeatureLevel;

	//장치 생성.
	ThrowIfFailed(D3D11CreateDevice(
		nullptr //안만들어 없으니, null 해주면 된다.
		,D3D_DRIVER_TYPE_HARDWARE	//장치만 쓰고싶은경우, 행들값
		,nullptr
		,flag	//flag 값
		,featureLevels	//피쳐레벨 - 라이브러리 버전, 생성할
		,_countof(featureLevels)	//배열 안 원소
		,D3D11_SDK_VERSION	//매크로 써야 함.
		,&device	//
		,&outFeatureLevel//,nullptr	// 선택사항임, 위에서, 무슨 버전 써는지,출력해서 담음.
		,&context
	)
		,TEXT("Failed to create device.")	 //ThrowIfFailed 매크로 만들었고, 2 번인자해당부분,
	);

	//IDXGIFactory 리소스 생성
	IDXGIFactory* factory = nullptr;
	CreateDXGIFactory(IID_PPV_ARGS(&factory));	//메크로 만들어 졌고,	//CreateDXGIFactory(__uuidof(factory),reinterpret_cast<void**>(&factory));

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
	//스왑체인 정보 구조체
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};	//주소값 보낼거야
	swapChainDesc.Windowed = true;				//창모드?
	swapChainDesc.OutputWindow = window;
	swapChainDesc.BufferUsage= DXGI_USAGE_RENDER_TARGET_OUTPUT;	//사용목적 지정
	swapChainDesc.BufferCount =2;			//백버퍼 개수.DXGI_SWAP_EFFECT_FLIP_DISCARD 사용시, 2로 변경되어야 함.
	swapChainDesc.SampleDesc.Count =1;		//멀티 샘플링 개수.	//1개한다는건, 안쓰겠다는 거임
	swapChainDesc.SampleDesc.Quality=0;		//멀티 샘플링 수준.
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//RGB unNormal?
	//swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;	//0,1 주로 사용한다 하드웨어 빨라서, 1해도 잘 나온데, 예전엔 잔상남았엇따?
	//swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;	//DXGI_SWAP_EFFECT_DISCARD legacy 오류나서 변경
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;	//DXGI_SWAP_EFFECT_DISCARD legacy 오류나서 변경

	//D3D_FEATURE_LEVEL targetLevel;

	//위에서 만들어서 주석처리
	//장치 생성
	//ThrowIfFailed(D3D11CreateDeviceAndSwapChain(nullptr,D3D_DRIVER_TYPE_HARDWARE,nullptr
	//	,flag,featureLevels,_countof(featureLevels),D3D11_SDK_VERSION,&swapChainDesc
	//	,&swapChain,&device,nullptr/*targetLevel*/,&context),TEXT("fail to D3D11CreateDeviceAndSwapChain"));

	//스왑체인 생성
	ThrowIfFailed(
		factory->CreateSwapChain(
		device
		,&swapChainDesc
		,&swapChain
	)
		,TEXT("failed to create swap chain.")
	);

	//이미지 그리는 대상 (=렌더타겟) 뷰 생성 : 크기는 창 크기와 같아야 한다.
	ID3D11Texture2D* backbuffer = nullptr; //받아올려고, 포인터타입으로...

	//대체
	//auto result =swapChain -> GetBuffer(0,IID_PPV_ARGS(&backbuffer));	//ㄴ 메크로! <- //swapChain -> GetBuffer(0,__uuidof(backbuffer),reinterpret_cast<void**> (&backbuffer));

	ThrowIfFailed(
		swapChain -> GetBuffer(0,IID_PPV_ARGS(&backbuffer)
	)
		,TEXT("fail to get back buffer")
	);

	//대체
	//if(FAILED(result))//결과 확인
	//{
	//	MessageBoxA(nullptr,"fail to get back buffer ","ERROR",MB_OK);
	//	__debugbreak();
	//}

	ThrowIfFailed(
		device -> CreateRenderTargetView(backbuffer,nullptr,&renderTargetView
	)
		,TEXT("fail to CreateRenderTargetView")
	);

	//사용한 리소스 해제 backbuffer
	backbuffer->Release();
	backbuffer= nullptr;

	//대체
	//result=	device -> CreateRenderTargetView(backbuffer,nullptr,&renderTargetView);

	//대체
	//if(FAILED(result))	//결과 확인
	//{
	//	MessageBoxA(nullptr,"fail to CreateRenderTargetView  ","ERROR",MB_OK);
	//	__debugbreak();
	//}

	//렌더 타겟 뷰 바인딩(연결)
	context -> OMSetRenderTargets(1,&renderTargetView,nullptr);

	//뷰 포트(화면)
	viewport.TopLeftX = (float)width/2;		//뷰포트 화면 설정하는 부분
	viewport.TopLeftY = (float)height/2;	//뷰포트 화면 설정하는 부분
	viewport.TopLeftX = 0.f;
	viewport.TopLeftY = 0.f;
	viewport.Width = (float)width;
	viewport.Height= (float)height;
	viewport.MaxDepth = 1.f;
	viewport.MinDepth= 0.f;

	//퓨 포트 설정
	context -> RSSetViewports(1,&viewport);
}
Renderer::~Renderer()
{
	//DX 리소스 해제
	if(context)
	{
		context->Release();
		context = nullptr;
	}
	if(swapChain)
	{
		swapChain->Release();
		swapChain = nullptr;
	}
	if(renderTargetView)
	{
		renderTargetView->Release();
		renderTargetView = nullptr;
	}
	if(device)
	{
		device->Release();
		device = nullptr;
	}
}
void Renderer::Draw(std::shared_ptr<class Level> level)
{
	//화면 크기 변경 중일 떄는 종료.
	if(isResizing)
	{
		return;
	}
	//그리기 전 작업
	context->OMSetRenderTargets(1,&renderTargetView,nullptr);//초기화 전에 바인딩하고,

	// 	   # 지우기
	//float color[] = {.6f,.7f,.8f,1.f};
	float color[] = {.7f,.8f,.95f,1.f};
	context->ClearRenderTargetView(renderTargetView,color);

	//Draw

	//카메라 바인딩.
	if(level->GetCamera())
	{
		level->GetCamera()->Draw();
	}

	for(uint32 ix = 0; ix <level->ActorCount(); ix++)
	{
		//액터 가져오기
		auto actor = level->GetActor(ix);
		if(actor->IsActive())
		{
			actor->Draw();
		}	//Draw
	}

	//버퍼교환 -모니터 싱글 (EndScene/ Present)
	swapChain->Present(1u,0u);
}
void Renderer::OnResize(uint32 width,uint32 height)
{
	//창 변경으로 인해, 리소스 크기 조정.
	if(!device || !context || !swapChain)
	{
		return;
	}
	isResizing = true;

	//context 비우기

	//렌더 타겟 해제
	//스왑체인 백버퍼 크기 변경
	//렌더 타겟 재생성/
	//뷰포트 업데이트.
	isResizing = false;
}
}