#pragma once
#include <d3d11.h>
#include <dxgi.h>
#include <memory>

#include "../Core/Type.h"
namespace Blue
{
class Renderer	//그래픽카드에서 처리하는 일/리소스를 관리하는 클래스 //RHI - Render Hardware Interface.
{
	friend class Engine;		//엔진 클래스 friend 선언.

public:
	Renderer()=default;
	Renderer(uint32 width,uint32 height,HWND window);
	~Renderer();

	//그리기 함수
	void Draw(std::shared_ptr<class Level> level);

private:

	//리소스 //장치류.
	ID3D11Device* device = nullptr;				//디바이스 - 생성목적
	ID3D11DeviceContext* context = nullptr;		//생성리소스 -그래픽카드에 연결 전달하는 일을 함 - 실 드로우 콜을 담당한다.
	IDXGISwapChain* swapChain = nullptr;		//백 버퍼 관리하는 주체.//그림그리면, 이미지 하나 더 있어서, 다른 이미지에 그린 후, 모니터랑 바꾼다. swap //모니터에 그린느것을 front /back buffer //전면버퍼, 후면버퍼 //바꿔치는 역할

	ID3D11RenderTargetView* renderTargetView = nullptr;		//리소스 //버퍼.

	D3D11_VIEWPORT viewport;	//리소스 //뷰포트.
};
}