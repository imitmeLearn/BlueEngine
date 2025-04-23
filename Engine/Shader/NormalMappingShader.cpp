#include "NormalMappingShader.h"
#include "Render/Texture.h"

namespace Blue
{
NormalMappingShader::NormalMappingShader()
	:Shader(TEXT("NormalMapping"))
{}
void NormalMappingShader::Bind()
{
	Shader::Bind();

	//텍스쳐 바인딩.
	for(const auto& textureRef : textures)
	{
		//약참조 하고 있는 원본 텍스쳐가 유요한지 확인.
		std::shared_ptr<Texture> texture = textureRef.second.lock();
		if(texture)
		{
			texture->Bind((uint32)textureRef.first);	//간단

			//인텍스 지정해서, 바인딩.
			texture->Bind(
				static_cast<uint32> (textureRef.first)
			);											//원형
		}
	}
}
void NormalMappingShader::SetTexture(ETextureBindType bindType,const std::weak_ptr<class Texture>& newTexture)
{
	//맵에 추가
	textures.insert(std::make_pair(bindType,newTexture));
}
}