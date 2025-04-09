#include "QuadMesh.h"
#include "Shader/Shader.h"
#include "Shader/TextureMappingShader.h"
#include "Resource\ShaderLoader.h"
#include "Resource\ModelLoader.h"

#include "Math\Matrix4.h"
#include "Math\Vector3.h"
namespace Blue
{
QuadMesh::QuadMesh()
{
	// 모델로더
	std::weak_ptr<MeshData> mesh;
	if(ModelLoader::Get().Load("quad.obj",mesh))
	{
		meshes.emplace_back(mesh);
	}

	//shaders.emplace_back(std::make_shared<Shader>());	//텍스처 추가했기에, 그대로 하면, 검정화면 나옴.
	//shaders.emplace_back(std::make_shared<TextureMappingShader>("T_coord.png"));
	std::weak_ptr<TextureMappingShader> shader;
	if(ShaderLoader::Get().Load<TextureMappingShader>(shader,"T_coord.png"))
	{
		//shaders.emplace_back(shader);
	}
}
void QuadMesh::Update(float deltaTime)
{
	//회전처리
	static float angle = 0.f;
	angle += 60.f * deltaTime;

	//회전 적용
	//transform.rotation.z = angle;
	//	transform.rotation.x = angle / 2.f;
	//transform.scale.x = angle;
	//transform.position.x = angle;
}
void QuadMesh::Rotate(float angle)
{
	/*
	std::vector<Vertex> vertices = //정점 배열 //원본
	{
		//texCoord 추가
		Vertex(Vector3(-0.5f,0.5f,0.5f),Vector3(1.0f,0.0f,0.0f),Vector2(0.0f,0.0f)),
		Vertex(Vector3(0.5f,0.5f,0.5f),Vector3(0.0f,1.0f,0.0f),Vector2(1.0f,0.0f)),
		Vertex(Vector3(0.5f,-0.5f,0.5f),Vector3(0.0f,0.0f,1.0f),Vector2(1.0f,1.0f)),
		Vertex(Vector3(-0.5f,-0.5f,0.5f),Vector3(1.0f,1.0f,0.0f),Vector2(0.0f,1.0f)),
	};

	static std::vector<Vertex> result;
	static bool hasInitialized = false;
	if(!hasInitialized)
	{
		hasInitialized = true;
		result.assign(vertices.begin(),vertices.end());	//배열 복사
	}

	//회전처리 . angle 누적해 전달할 예쩡.
	//Matrix4 rotation = Matrix4::RotationX(angle);
	//Matrix4 rotation = Matrix4::RotationY(angle);
	Matrix4 rotation = Matrix4::RotationZ(angle);
	result[0].position = vertices[0].position * rotation;
	result[1].position = vertices[1].position * rotation;
	result[2].position = vertices[2].position * rotation;
	result[3].position = vertices[3].position * rotation;

	//메시 정점 버퍼 업데이트,// 원점은 유지하고ㅡ 원래값에 회전행렬 곱하면, 실제 정점에 행렬곱하는것이다. 뭐가 회전에, 점이 회전함.
	meshes[0].lock()->UpdateVertexBuffer(result);
	*/
}
}