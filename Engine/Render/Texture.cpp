#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Library\stbi_image.h"

#include <iostream>
namespace Blue
{
Texture::~Texture()
{}
Texture::Texture(const std::string & name,BindType bindType,uint32 index)
	:name(name),bindType(bindType)
{
	LoadTexture(name);
}
void Texture::Bind(uint32 index)
{
	//예외처리
	if(!textureData)
	{
		return;
	}

	static ID3D11DeviceContext& context = Engine::Get().Context	(); //컨텍스트 열기

	// 바인딩.
	if(bindType == BindType::VertexShader)
	{
		context.VSSetShaderResources(index,1,&textureData->shaderResourceView);
		context.VSSetSamplers(index,1,&textureData->samplerState);
	}

	else if(bindType == BindType::PixelShader)
	{
		context.PSSetShaderResources(index,1,&textureData->shaderResourceView);
		context.PSSetSamplers(index,1,&textureData->samplerState);
	}
}
//이미지 로드
void Texture::LoadTexture(const std::string& name)
{
	//경로설정
	char path[256] = {};
	sprintf_s(path,256,"../Assets/Textures/%s",name.c_str()); //주소 오타주의1"!!!!!!!!

	//객체생성
	textureData = std::make_unique<TextureData>();

	//이미지 파일 로드 :
	textureData->data = stbi_load(
		path
		,&textureData->width
		,&textureData->height
		,&textureData->channelCount
		,0
	);

	//예외처리
	if(!textureData -> data)
	{
		std::cout<<"Error : Failed to load texture file: " << name << "\n";
		__debugbreak;
	}

	//DX 리소스 생성
	static ID3D11Device& device = Engine::Get().Device();	//생성은, 장치가 담당! 장치 얻어오기 //보통, 쓰는거 글로벌하게 빼놓음. 이렇게 중간에 가져오는거 안좋기에!!!!

	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.ArraySize = 1;
	textureDesc.MipLevels = 1;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.Width = textureData->width;
	textureDesc.Height = textureData->height;

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = textureData->data;	//이건 2차원일떄만, 텍스쳐의 경우에 특히!
	data.SysMemPitch = textureData->width * textureData->channelCount;	//이건 2차원일떄만, 텍스쳐의 경우에 특히!

	ID3D11Texture2D* texture = nullptr;
	auto result = device.CreateTexture2D(&textureDesc,&data,&texture);	//인자 셋다 주소를 달라했으니..
	if(FAILED(result))
	{
		std::cout<<"Error : Failed to Create - texture2d " << name << "\n";
		__debugbreak;
	}

	//쉐이더 리소스 뷰 생성(바인딩할 리소스) //생성 리소스기반으로 뷰 작성 ㅣ 뷰 있어야, 그래픽 카드와 소통 가능해!
	//쉐이더 리소스 뷰이면서, 렌더타겟으로 사용한다면,.. G-Buffer, Normal-Buffer, ...거기에서 샘플링 다시 해서, 계산한다.??
	result = device.CreateShaderResourceView(texture,nullptr,&textureData->shaderResourceView);
	if(FAILED(result))
	{
		std::cout<<"Error : Failed to Create -  CreateShaderResourceView " << name << "\n";
		__debugbreak;
	}

	if(texture)
	{
		texture->Release(); //쓰임을 다함.
		texture = nullptr;
	}

	#pragma region //샘플러 생성 - 픽셀의 색상 가져와줘. 함수가 요구하는 인자의 구조체 확인하고 들어가서 세팅정보 확인
	//typedef struct D3D11_SAMPLER_DESC //함수가 요구하는 인자의 구조체에서 요구하는 세팅정보 확인
	//{
	//	D3D11_FILTER Filter;
	//	D3D11_TEXTURE_ADDRESS_MODE AddressU;
	//	D3D11_TEXTURE_ADDRESS_MODE AddressV;
	//	D3D11_TEXTURE_ADDRESS_MODE AddressW;
	//	FLOAT MipLODBias;		//pass
	//	UINT MaxAnisotropy;		//pass
	//	D3D11_COMPARISON_FUNC ComparisonFunc;
	//	FLOAT BorderColor[4]; //pass
	//	FLOAT MinLOD;
	//	FLOAT MaxLOD;
	//} 	D3D11_SAMPLER_DESC;
	#pragma endregion
	CD3D11_SAMPLER_DESC sampleDesc = {};
	sampleDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	sampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampleDesc.MaxLOD = FLT_MAX;
	//sampleDesc.MinLOD = FLT_MAX;
	//sampleDesc.MinLOD =	FLT_MIN;
	sampleDesc.MinLOD = -FLT_MAX;
	sampleDesc.MaxAnisotropy = 3;
	sampleDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;

	//샘플러 생성
	result =
		device.CreateSamplerState(&sampleDesc,&textureData->samplerState);
	if(FAILED(result))
	{
		std::cout<<"Error : Failed to Create -  CreateSamplerState " << name << "\n";
		__debugbreak;
	}
}
}