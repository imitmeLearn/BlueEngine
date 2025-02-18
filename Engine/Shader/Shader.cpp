#include "Shader.h"

#include <d3dcompiler.h>
#include "../Core/Engine.h"
namespace Blue
{
Shader::~Shader()
{
	//DX 리소스 해제
	if(inputlayout)
	{
		inputlayout->Release();
	}
	if(vertexShader)
	{
		vertexShader->Release();
	}
	if(pixelShader)
	{
		pixelShader->Release();
	}
	if(vertexShaderBuffer)
	{
		vertexShaderBuffer->Release();
	}
	if(pixelShaderBuffer)
	{
		pixelShaderBuffer->Release();
	}
}
Shader::Shader(const std::wstring& name)
	:name(name)
{
	//경로 추가
	wchar_t path[256]={};
	swprintf_s(path,256,L"HLSLShader/%sVertexShader.hlsl",name.c_str());

	//쉐이더 컴파일,
	auto result = D3DCompileFromFile(
		//TEXT("../Shader/VertexShader.hlsl"),nullptr,nullptr,"main","vs_5_0",0,0	//안돼
		//TEXT("Shader/VertexShader.hlsl")
		path
		  ,nullptr,nullptr,"main","vs_5_0",0,0
			  ,&vertexShaderBuffer /*컴파일한 결과 obj 나오면, 임시로 저장하고 이를 기준으로 쉐이더 생성하니까.*/
			  ,nullptr);
	if(FAILED(result))	//결과 확인
	{
		MessageBoxA(nullptr,"fail to D3DCompileFromFile -vertex shader ","ERROR",MB_OK);
		__debugbreak();
	}
	//장치 객체 생성
	ID3D11Device& device = Engine::Get().Device();

	//쉐이더 생성/
	result=	device.CreateVertexShader(vertexShaderBuffer->GetBufferPointer()
			,vertexShaderBuffer->GetBufferSize()
			,nullptr
			,&vertexShader
	);
	if(FAILED(result))	//결과 확인
	{
		MessageBoxA(nullptr,"fail to CreateVertexShader -vertex shader ","ERROR",MB_OK);
		__debugbreak();
	}
	#pragma region //입력 레이아웃, //정점 쉐이더에 전달할 정점 데이터가 어떻게 생겼는지 알려줌.

	//입력 레이아웃, //정점 쉐이더에 전달할 정점 데이터가 어떻게 생겼는지 알려줌.
	//typedef struct D3D11_INPUT_ELEMENT_DESC
	//{
	//	LPCSTR SemanticName;
	//	UINT SemanticIndex;
	//	DXGI_FORMAT Format;	//생김새
	//	UINT InputSlot;		//슬롯지정
	//	UINT AlignedByteOffset;
	//	D3D11_INPUT_CLASSIFICATION InputSlotClass;	//점정 쉐이더 같으면, instance 쓰면 되고 //
	//	UINT InstanceDataStepRate;
	//}
	#pragma endregion
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT, /*별도로 쓰는게 없어서*/0, /*하나밖에없어서*/0
		,D3D11_INPUT_PER_VERTEX_DATA,0}
		//,{"COLOR",0,DXGI_FORMAT_R32G32B32_FLOAT /*4+4+4*/,0,12,D3D11_INPUT_PER_VERTEX_DATA,0} //4+4+4=12
		,{"COLOR",0,DXGI_FORMAT_R32G32B32_FLOAT /*4+4+4*/,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0} //위랑 같은 결과!
	};

	result = device.CreateInputLayout(
		inputDesc
		,_countof(inputDesc)
		,vertexShaderBuffer->GetBufferPointer()
		,vertexShaderBuffer->GetBufferSize()
		,&inputlayout
	);
	if(FAILED(result))	//결과 확인
	{
		MessageBoxA(nullptr,"fail to CreateInputLayout ","ERROR",MB_OK);
		__debugbreak();
	}

	swprintf_s(path,256,L"HLSLShader/%sPixelShader.hlsl",name.c_str());

	//픽셀 쉐이더 컴파일/생성.////
	result = D3DCompileFromFile(
	//TEXT("../Shader/PixelShader.hlsl"),nullptr,nullptr,"main","vs_5_0",0,0	//안돼
	//TEXT("Shader/PixelShader.hlsl")
		path
		,nullptr,nullptr,"main","ps_5_0",0,0
		,&pixelShaderBuffer /*컴파일한 결과 obj 나오면, 임시로 저장하고 이를 기준으로 쉐이더 생성하니까.*/
		,nullptr);
	if(FAILED(result))	//결과 확인
	{
		MessageBoxA(nullptr,"fail to D3DCompileFromFile -pixel shader ","ERROR",MB_OK);
		__debugbreak();
	}

	//쉐이더 생성/
	result=	device.CreatePixelShader(pixelShaderBuffer->GetBufferPointer()
			,pixelShaderBuffer->GetBufferSize()
			,nullptr
			,&pixelShader
	);
	if(FAILED(result))	//결과 확인
	{
		MessageBoxA(nullptr,"fail to CreatePpixelShader -pixel shader ","ERROR",MB_OK);
		__debugbreak();
	}
}
void Shader::Bind()
{
	//장치 문맥(DeviceContext) 얻어오기
	static ID3D11DeviceContext& context = Engine::Get().Context();

	//입력 레이아웃 전달
	context.IASetInputLayout(inputlayout);

	//조립할 모양 설정
	//선을 그리더라도, 미세하게 삼각형 만들어 조합
	context.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//쉐이더 설정
	context.VSSetShader(vertexShader,nullptr,0);
	context.PSSetShader(pixelShader,nullptr,0);
}
}