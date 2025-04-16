#include "TextureMappingShader.h"
#include "Render\Texture.h"
namespace Blue
{
	TextureMappingShader::TextureMappingShader()
		:Shader(L"TextureMapping")
	{
	}
	//TextureMappingShader::TextureMappingShader(const std::string& textureName)
	//	:Shader(L"TextureMapping")
	//{
	//	//texture = std::make_unique<Texture>(textureName);	//텍스쳐 생성
	//	TextureLoader::Get().Load(textureName, texture);
	//}
	//TextureMappingShader::TextureMappingShader(const std::wstring& name, const std::string& textureName)
	//	:Shader(name)
	//{
	//	//	texture = std::make_unique<Texture>(textureName);	//텍스쳐 생성
	//	TextureLoader::Get().Load(textureName, texture);
	//}
	void TextureMappingShader::SetTexture(const std::weak_ptr<class Texture>& newTexture)
	{
		//내부 텍스처 값 설정.
		texture = newTexture;
	}
	void TextureMappingShader::Bind()
	{
		Shader::Bind();
		if (texture.lock())
		{
			texture.lock()->Bind();
		}
	}
}