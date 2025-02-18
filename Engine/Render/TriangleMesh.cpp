#include "TriangleMesh.h"
#include "Vertex.h"
#include "../Shader/Shader.h"

namespace Blue
{
TriangleMesh::TriangleMesh()
{
	std::vector<Vertex> vertices = //정점 배열
	{
		Vertex(Vector3(0.f,0.5f,0.5f))
		,Vertex(Vector3(0.5f,-0.5f,0.5f))
		,Vertex(Vector3(-0.5f,-0.5f,0.5f)),
	};

	std::vector<uint32> indices =	//인덱스 배열
	{
		0,1,2
	};

	meshes.emplace_back(std::make_shared<MeshData>(vertices,indices));
	shaders.emplace_back(std::make_shared<Shader>());
}
}