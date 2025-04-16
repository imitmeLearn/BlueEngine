#include "DemoLevel.h"

#include "Actor\Actor.h"
#include "Actor\QuadActor.h"
#include "Actor\CameraActor.h"

#include "Render\QuadMesh.h"

#include "Resource\ShaderLoader.h"
#include "Resource\ModelLoader.h"
#include "Resource\TextureLoader.h"

#include "Shader\TextureMappingShader.h"

#include "Component\StaticMeshComponent.h"
#include "Component\CameraComponent.h"

#include "Math\Transform.h"
#include "Math\Vector3.h"

namespace Blue

{
DemoLevel::DemoLevel()
{
	//데모 씬 구성

	std::shared_ptr<QuadActor> actor = std::make_shared<QuadActor>();	//액터생성
	actor -> transform.position.x = -1.f;
	//actor -> transform.scale = Vector3::One * 0.5f;

	std::shared_ptr<QuadActor> actor2 = std::make_shared<QuadActor>();
	//actor2->transform.scale = Vector3::One * 0.5f;
	actor2->transform.position.x = 1.f;

	//카메라 액터 생성
	//std::shared_ptr<Actor> cameraActor = std::make_shared<Actor>();
	//cameraActor->transform.position.y = -0.5f;
	//cameraActor->AddComponent(std::make_shared<CameraComponent>());
	std::shared_ptr<CameraActor> cameraActor = std::make_shared<CameraActor>();
	cameraActor->transform.position.z = -3.f;

	//엑터를 레벨에 추가
	AddActor(actor);
	AddActor(actor2);
	AddActor(cameraActor);	//this->cameraActor = cameraActor;
}
DemoLevel::~DemoLevel()
{}
}