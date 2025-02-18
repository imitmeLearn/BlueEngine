#include "Renderer.h"
#include <vector>
#include <d3dcompiler.h>
#include"../Math/Vector3.h"
#include "../Shader/Shader.h"

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
	Vector3 vertices[] =
	{
		//화면 기본 좌표,
		Vector3(0.f,0.5f,0.5f)
		,Vector3(0.5f,-0.5f,0.5f)
		,Vector3(-0.5f,-0.5f,0.5f)
	};

	//각 리소스 바인딩.
}
Renderer::~Renderer()
{}
void Renderer::Draw()
{
	//쉐이더 객체 생성
	if(shader == nullptr)
	{
		shader = std::make_unique<Shader>();
	}

	//그리기 전 작업
	// 	   # 지우기
	//float color[] = {.6f,.7f,.8f,1.f};
	float color[] = {.7f,.8f,.95f,1.f};
	context->ClearRenderTargetView(renderTargetView,color);
	//드로우

	//리소스 바인딩. //정점쉐이더가 실행되기 전 단계
	//정점 버퍼 전달
	static unsigned int stride = Vector3::Stride();
	static unsigned int offset = 0;
	context -> IASetVertexBuffers(0,1,&vertexBuffer,/*요소하나의 크기 얼마냐*/&stride,&offset);

	//인덱스 버퍼 전달
	context ->IASetIndexBuffer(indexBuffer, /*d인덱스 요소 하나의 크기는 얼마냐 - wjscp */ DXGI_FORMAT_R32_UINT,0);

	shader->Bind();

	//드로우콜
	context->DrawIndexed(3,0,0);

	//버퍼교환 -모니터 싱글

	swapChain->Present(1u,0u);
}
}