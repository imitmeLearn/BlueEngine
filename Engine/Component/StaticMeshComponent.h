#pragma once
#include "Component.h"
#include <vector>
#include <memory>
namespace Blue
{
class StaticMeshComponent: public Component
{
public:
	StaticMeshComponent();
	~StaticMeshComponent();
	//그리기 함수
	virtual void Draw() override;
	//메시 설정 함수.
	void SetMesh(std::shared_ptr<class Mesh> nesMesh);
	//셰이더 설정 함수.
	void AddShader(std::weak_ptr<class Shader> newShader);

private:
	std::shared_ptr<class Mesh> mesh;		//메시(모델링)데이터
	std::vector<std::weak_ptr<class Shader>> shaders;	//셰이더 : 서브메시 수 만큼 필요
};
}