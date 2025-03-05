#include "TextureMappingShader.h"
#include "Render\Texture.h"
namespace Blue
{
TextureMappingShader::TextureMappingShader()
	:Shader(L"TextureMapping")
{}
TextureMappingShader::TextureMappingShader(const std::string & textureName)
	:Shader(L"TextureMapping")
{
	texture = std::make_unique<Texture>(textureName);	//텍스쳐 생성
}
TextureMappingShader::TextureMappingShader(const std::wstring & name,const std::string & textureName)
	:Shader(name)
{
	texture = std::make_unique<Texture>(textureName);	//텍스쳐 생성
}
void TextureMappingShader::Bind()
{
	Shader::Bind();
	if(texture)
	{
		texture ->Bind();
	}
}
}