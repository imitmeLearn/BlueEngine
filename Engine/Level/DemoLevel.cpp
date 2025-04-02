#include "DemoLevel.h"

#include "Actor\Actor.h"
#include "Actor\QuadActor.h"

#include "Render\QuadMesh.h"

#include "Resource\ShaderLoader.h"
#include "Resource\ModelLoader.h"
#include "Resource\TextureLoader.h"

#include "Shader\TextureMappingShader.h"

#include "Component\StaticMeshComponent.h"

#include "Math\Transform.h"
#include "Math\Vector3.h"

namespace Blue

{
DemoLevel::DemoLevel()
{
	//데모 씬 구성

	std::shared_ptr<QuadActor> actor = std::make_shared<QuadActor>();	//액터생성
	actor -> transform.position.x = 0.5f;
	actor -> transform.scale = Vector3::One * 0.5f;

	//엑터를 레벨에 추가
	AddActor(actor);
}
DemoLevel::~DemoLevel()
{}
}