#include "QuadActor.h"
#include "Component\StaticMeshComponent.h"
#include "Render\QuadMesh.h"
#include "Render\SphereMesh.h"
#include "Shader\TextureMappingShader.h"
#include "Resource\ShaderLoader.h"
namespace Blue

{
QuadActor::QuadActor()
{
	std::shared_ptr<StaticMeshComponent> meshComponent//스태틱 메시 컴포넌트 생성
		= std::make_shared<StaticMeshComponent>();

	AddComponent(meshComponent);		//엑터에 컴포넌트 추가

	//컴포넌트 설정 (원)
	std::shared_ptr<QuadMesh> quadMesh = std::make_shared<QuadMesh>();
	//meshComponent->SetMesh(quadMesh);

	////컴포넌트 설정 (축약)
	meshComponent->SetMesh(std::make_shared<SphereMesh>());

	////리소스 로드
	std::weak_ptr<TextureMappingShader> shader;
	//if(ShaderLoader::Get().Load<TextureMappingShader>(shader,"T_coord.png"))
	if(ShaderLoader::Get().Load<TextureMappingShader>(shader,"T_White.png"))
	{
		meshComponent-> AddShader(shader);
	}
}
}