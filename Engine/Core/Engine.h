#pragma once

#include <memory> //스마트포인터
#include <Windows.h>
#include <string>
#include "Type.h"
#include <d3d11.h>

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

	//싱글톤 접근 함수.
	static Engine& Get();

	//GETTER.
	ID3D11Device& Device() const;
	ID3D11DeviceContext& Context() const;

protected:

	std::shared_ptr<class Window> window;		//창 객체
	std::shared_ptr<class Renderer> renderer;	//렌더러 객체
	std::unique_ptr<class ShaderLoader> shaderLoader;	//셰이더로더 객체
	std::unique_ptr<class TextureLoader> textureLoader;	//텍스쳐로더 객체
	std::unique_ptr<class ModelLoader> modelLoader;		//모델 로더 객체
	static Engine* instance;					//싱글톤 객체

private:
};
}