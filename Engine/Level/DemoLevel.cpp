#include "DemoLevel.h"

#include "Actor\Actor.h"
#include "Render\QuadMesh.h"

#include "Resource\ShaderLoader.h"
#include "Resource\ModelLoader.h"
#include "Resource\TextureLoader.h"

#include "Shader\TextureMappingShader.h"

#include "Component\StaticMeshComponent.h"

namespace Blue

{
DemoLevel::DemoLevel()
{
	//데모 씬 구성

	std::shared_ptr<Actor> actor = std::make_shared<Actor>();	//액터생성
	std::shared_ptr<StaticMeshComponent> meshComponent//스태틱 메시 컴포넌트 생성
		= std::make_shared<StaticMeshComponent>();
	actor->AddComponent(meshComponent);		//엑터에 컴포넌트 추가

	////리소스 로드 및 컴포넌트 설정
	std::shared_ptr<QuadMesh> quadMesh = std::make_shared<QuadMesh>();
	meshComponent->SetMesh(quadMesh);
	std::weak_ptr<TextureMappingShader> shader;
	if(ShaderLoader::Get().Load<TextureMappingShader>(shader,"T_coord.png"))
	{
		meshComponent-> AddShader(shader);
	}

	//엑터를 레벨에 추가
	AddActor(actor);
}
DemoLevel::~DemoLevel()
{}
}