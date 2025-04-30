#pragma once

#include "Core\Engine.h"
#include <string>
#include <d3d11.h>
#include <memory>
namespace Blue
{
struct TextureData
{
	TextureData() = default;
	~TextureData()
	{
		if(data)
		{
			free(data);
			data = nullptr;
		}
		if(shaderResourceView)
		{
			shaderResourceView -> Release();
			shaderResourceView = nullptr;
		}
		if(samplerState)
		{
			samplerState -> Release();
			samplerState = nullptr;
		}
	}

	//텍스쳐 원시 데이터
	int32 width =0;		//Core\Type.h // int32
	int32 height =0;
	int32 channelCount =0;
	void* data = nullptr;

	//DX 리소스  //#include <d3d11.h>
	ID3D11ShaderResourceView* shaderResourceView = nullptr;
	ID3D11SamplerState* samplerState = nullptr;
};

class Texture	//텍스쳐 클래스
{
	enum class BindType
	{
		VertexShader
		,PixelShader
	};

public:
	Texture() = default;
	~Texture();
	Texture(const std::string& name
			,BindType bindType = BindType::PixelShader
			,uint32 index = 0u);//텍스쳐 순번
	void Bind(uint32 index=0);
protected:	//접근가능하도록
	void LoadTexture(const std::string& name);
protected:	//접근가능하도록
	std::string name;	//이미지 이름
	BindType bindType = BindType::PixelShader;	//바인딩 쉐이더 타입
	std::unique_ptr<TextureData> textureData;	//텍스처 데이터
};
}