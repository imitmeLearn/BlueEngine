#pragma once
#include "Shader.h"
#include <memory>
#include "Resource\TextureLoader.h"
namespace Blue
{
class TextureMappingShader: public Shader
{
public:
	TextureMappingShader();
	TextureMappingShader(const std::string& textureName);
	TextureMappingShader(
		const std::wstring& name = L"Default"
		,const std::string& textureName = ""
	);
	virtual void Bind() override;
private:
	//std::unique_ptr<class Texture> texture;
	std::weak_ptr<class Texture> texture;
};
}