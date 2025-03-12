#include "QuadMesh.h"
#include "Shader/Shader.h"
#include "Shader/TextureMappingShader.h"
#include "Resource\ShaderLoader.h"

#include "Math\Matrix4.h"
#include "Math\Vector3.h"
namespace Blue
{
QuadMesh::QuadMesh()
{
	std::vector<Vertex> vertices = //정점 배열
	{
		//Vertex(Vector3(0.f,0.5f,0.5f))
		//,Vertex(Vector3(0.5f,-0.5f,0.5f))
		//,Vertex(Vector3(-0.5f,-0.5f,0.5f))	//삼각형 	indices =//0,1,2,3	//삼각형

		//Vertex(Vector3(-0.5f,-0.5f,0.5f))
		//,Vertex(Vector3(-0.5f,0.5f,0.5f))
		//,Vertex(Vector3(0.5f,0.5f,0.5f))
		//,Vertex(Vector3(0.5f,-0.5f,0.5f)) //indices	//1,2,3,1,3,4	//직사각형

		//Vertex(Vector3(-0.5f,0.5f,0.5f))
		//,Vertex(Vector3(0.5f,0.5f,0.5f))
		//,Vertex(Vector3(0.5f,-0.5f,0.5f))
		//,Vertex(Vector3(-0.5f,-0.5f,0.5f)) //직사각형 indices	//0,1,3,1,2,3	//직사각형

		//Vertex(Vector3(-0.5f,0.5f,0.5f))
		//,Vertex(Vector3(0.5f,0.5f,0.5f))
		//,Vertex(Vector3(0.5f,-0.5f,0.5f))
		//,Vertex(Vector3(-0.5f,-0.5f,0.5f)) //직사각형 indices	//0,1,3,1,2,3	//직사각형

		////평행사변형 0,1,2,0,2,3	//평행사변형
		//Vertex(Vector3(0.f,0.5f,0.5f),Vector3(1.f,0.f,0.f))
		//,Vertex(Vector3(0.5f,-0.5f,0.5f),Vector3(0.f,1.f,0.f))
		//,Vertex(Vector3(-0.5f,-0.5f,0.5f),Vector3(0.f,0.f,1.f))
		//,Vertex(Vector3(-1.f,0.5f,0.5f),Vector3(1.f,1.f,0.f))// 0,1,2,2,3,0	//평행사변형 ㄲ 똑같이 나오는데??  하지만, 면이 뒤집힌거임

		//texCoord 추가
		Vertex(Vector3(-0.5f,0.5f,0.5f),Vector3(1.0f,0.0f,0.0f),Vector2(0.0f,0.0f)),
		Vertex(Vector3(0.5f,0.5f,0.5f),Vector3(0.0f,1.0f,0.0f),Vector2(1.0f,0.0f)),
		Vertex(Vector3(0.5f,-0.5f,0.5f),Vector3(0.0f,0.0f,1.0f),Vector2(1.0f,1.0f)),
		Vertex(Vector3(-0.5f,-0.5f,0.5f),Vector3(1.0f,1.0f,0.0f),Vector2(0.0f,1.0f)),
	};

	std::vector<uint32> indices =	//인덱스 배열
	{
		//0,1,2,0,2,3	//평행사변형
		0,1,3,1,2,3	//직사각형
	};

	//변환 -크기
	//vertices[0].position = vertices[0].position * Matrix4::Scale(0.5f);
	//vertices[1].position = vertices[1].position * Matrix4::Scale(0.5f);
	//vertices[2].position = vertices[2].position * Matrix4::Scale(0.5f);
	//vertices[3].position = vertices[3].position * Matrix4::Scale(0.5f);

	//변환 - 이동
	//vertices[0].position = vertices[0].position * Matrix4::Translation(0.5f,0.f,0.f);
	//vertices[1].position = vertices[1].position * Matrix4::Translation(0.5f,0.f,0.f);
	//vertices[2].position = vertices[2].position * Matrix4::Translation(0.5f,0.f,0.f);
	//vertices[3].position = vertices[3].position * Matrix4::Translation(0.5f,0.f,0.f);

	meshes.emplace_back(std::make_shared<MeshData>(vertices,indices));
	//shaders.emplace_back(std::make_shared<Shader>());	//텍스처 추가했기에, 그대로 하면, 검정화면 나옴.
	//shaders.emplace_back(std::make_shared<TextureMappingShader>("T_coord.png"));
	std::weak_ptr<TextureMappingShader> shader;
	if(ShaderLoader::Get().Load<TextureMappingShader>(shader,"T_coord.png"))
	{
		shaders.emplace_back(shader);
	}
}
void QuadMesh::Update(float deltaTime)
{
	//회전처리
	static float angle = 0.f;
	angle += 60.f * deltaTime;

	//Rotate(angle);
}
void QuadMesh::Rotate(float angle)
{
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
	meshes[0]->UpdateVertexBuffer(result);
}
}