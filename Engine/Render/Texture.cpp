#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Library\stbi_image.h"

#include <iostream>
namespace Blue
{
Texture::~Texture()
{}
Texture::Texture(const std::string & name,BindType bindType,uint32 index)
	:name(name),bindType(bindType),index(index)
{
	LoadTexture(name);
}
void Texture::Bind()
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
}
}