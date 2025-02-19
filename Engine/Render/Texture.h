#pragma once

#include "Core\Engine.h"

namespace Blue
{
struct TextureData
{
	TextureData() = default;
	~TextureData()
	{
		free(data);
		data = nullptr;

		shaderResourceView -> Release();
		shaderResourceView = nullptr;

		samplerState -> Release();
		samplerState = nullptr;
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
	~Texture();
	Texture(const std::string& name
			,BindType bindType = BindType::PixelShader
			,uint32 index = 0u);
	void Bind();
private:
	void LoadTexture(const std::string& name);
private:
	std::string name;	//이미지 이름
	uint32 index = 0;	//텍스처 순번
	BindType bindType = BindType::PixelShader;	//바인딩 쉐이더 타입
	std::unique_ptr<TextureData> textureData;	//텍스처 데이터
};
}