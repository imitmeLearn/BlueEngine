#pragma once
#include <string>
#include <d3d11.h>
namespace Blue
{
class Shader
{
public:
	virtual	~Shader();

	Shader(const std::wstring& name = L"Default");

	//GPU 쉐이더 객체를 연결(바인딩)하는 함수.
	virtual void Bind() ;
protected:

	std::wstring name;//쉐이더 이름

	ID3D11InputLayout* inputlayout = nullptr; //DX 리소스

	ID3D11VertexShader* vertexShader = nullptr;
	ID3D11PixelShader* pixelShader = nullptr;

	ID3DBlob* vertexShaderBuffer = nullptr;
	ID3DBlob* pixelShaderBuffer = nullptr;
};
}