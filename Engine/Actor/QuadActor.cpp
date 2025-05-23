﻿#include "QuadActor.h"
#include "Component\StaticMeshComponent.h"
#include "Render\QuadMesh.h"
#include "Render\Texture.h"
#include "Render\SphereMesh.h"
#include "Shader\TextureMappingShader.h"
#include "Shader\NormalMappingShader.h"
#include "Resource\ShaderLoader.h"
#include "Resource\TextureLoader.h"

namespace Blue

{
QuadActor::QuadActor()
{
	std::shared_ptr<StaticMeshComponent> meshComponent//스태틱 메시 컴포넌트 생성
		= std::make_shared<StaticMeshComponent>();

	AddComponent(meshComponent);		//엑터에 컴포넌트 추가

	//컴포넌트 설정 (원)
	//std::shared_ptr<QuadMesh> quadMesh = std::make_shared<QuadMesh>();
	//meshComponent->SetMesh(quadMesh);

	////컴포넌트 설정 (축약)
	meshComponent->SetMesh(std::make_shared<SphereMesh>());

	////리소스 로드
	std::weak_ptr<NormalMappingShader> shader;
	//if(ShaderLoader::Get().Load<TextureMappingShader>(shader,"T_coord.png"))
	if(ShaderLoader::Get().Load<NormalMappingShader>(shader))
	{
		meshComponent-> AddShader(shader);
	}

	//텍스쳐 로드 및 셰이더 에 설정
	std::weak_ptr<Texture> diffuseMap;
	TextureLoader::Get().Load("5k_earth_day_map.png",diffuseMap);
	shader.lock()->SetTexture(NormalMappingShader::ETextureBindType::Diffuse,diffuseMap);

	std::weak_ptr<Texture> normalMap;
	TextureLoader::Get().Load("8k_earth_normal_map.png",normalMap);
	shader.lock()->SetTexture(NormalMappingShader::ETextureBindType::NormalMap,normalMap);
}
void QuadActor::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);
	static const float rotationSpeed = 10.f;
	transform.rotation.y += deltaTime * rotationSpeed;	//회전 -> 점이 돈다.
}
}