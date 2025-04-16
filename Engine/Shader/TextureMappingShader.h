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
	//TextureMappingShader(const std::string& textureName);
	//TextureMappingShader(
	//	const std::wstring& name = L"Default"
	//	,const std::string& textureName = ""
	//);

	//텍스쳐 설정 함수.
	//기존엔 컴파일만 해줬었기에, 설정해주는 함수를 setter 로 추가
	void SetTexture(const std::weak_ptr<class Texture>& newTexture);

	virtual void Bind() override;
private:
	//std::unique_ptr<class Texture> texture;
	std::weak_ptr<class Texture> texture;
};
}