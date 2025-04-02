﻿#include "StaticMeshComponent.h"
#include "Render\Mesh.h"
#include "Shader\Shader.h"
#include "Core\Engine.h"
namespace Blue
{
StaticMeshComponent::StaticMeshComponent()
{}
StaticMeshComponent::~StaticMeshComponent()
{}	//메모리 관리 알아서 됨. 0
void StaticMeshComponent::Draw()
{
	uint32 meshCount = mesh->SubMeshCount();
	if(meshCount != (uint32)shaders.size())
	{
		return;
	}	//예외처리
	for(int ix = 0; ix < meshCount ; ++ix)//메시 순회하면서, DrawCall
	{
		auto subMesh = mesh -> GetSubMesh(ix);	//서브메시 가져오기
		if(subMesh.lock() && shaders[ix].lock())	//메시가 유효하면, Draw
		{
			subMesh.lock()->Bind();	//서브 메시 바인딩
			shaders[ix].lock()->Bind();	//셰이더 바인딩

			//Draw call
			static ID3D11DeviceContext& context = Engine::Get().Context();
			context.DrawIndexed(subMesh.lock()->IndexCount(),0u,0u);
		}
	}
}
void StaticMeshComponent::SetMesh(std::shared_ptr<Mesh> newMesh)
{
	mesh = newMesh;
}
void StaticMeshComponent::AddShader(std::weak_ptr<Shader> newShader)
{
	shaders.emplace_back(newShader);
}
}