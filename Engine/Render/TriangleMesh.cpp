#include "TriangleMesh.h"
#include "Vertex.h"
#include "../Shader/DefaultShader.h"
#include "Resource\/ShaderLoader.h"

namespace Blue
{
TriangleMesh::TriangleMesh()
{
	std::vector<Vertex> vertices = //정점 배열
	{
		/*	Vertex(Vector3(0.f,0.5f,0.5f),Vector3(1.f,0.f,0.f))
			,Vertex(Vector3(0.5f,-0.5f,0.5f),Vector3(0.f,1.f,0.f))
			,Vertex(Vector3(-0.5f,-0.5f,0.5f),Vector3(0.f,0.f,1.f)),*/

			//texCoord 추가
		Vertex(Vector3(0.0f,0.5f,0.5f),Vector3(1.0f,0.0f,0.0f),Vector2(0.5f,0.0f)),
		Vertex(Vector3(0.5f,-0.5f,0.5f),Vector3(0.0f,1.0f,0.0f),Vector2(1.0f,1.0f)),
		Vertex(Vector3(-0.5f,-0.5f,0.5f),Vector3(0.0f,0.0f,1.0f),Vector2(0.0f,1.0f)),
	};

	std::vector<uint32> indices =	//인덱스 배열
	{
		0,1,2
	};

	meshes.emplace_back(std::make_shared<MeshData>(vertices,indices));
	//shaders.emplace_back(std::make_shared<Shader>());
	std::weak_ptr<DefaultShader> shader;
	ShaderLoader::Get().Load<DefaultShader>(shader);
	//shaders.emplace_back(shader);
}
}