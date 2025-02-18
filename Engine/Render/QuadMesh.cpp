#include "QuadMesh.h"
#include "../Shader/Shader.h"
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

		//평행사변형 0,1,2,0,2,3	//평행사변형
		Vertex(Vector3(0.f,0.5f,0.5f))
		,Vertex(Vector3(0.5f,-0.5f,0.5f))
		,Vertex(Vector3(-0.5f,-0.5f,0.5f))
		,Vertex(Vector3(-1.f,0.5f,0.5f))// 0,1,2,2,3,0	//평행사변형 ㄲ 똑같이 나오는데??  하지만, 면이 뒤집힌거임
	};

	std::vector<uint32> indices =	//인덱스 배열
	{
		0,1,2,0,2,3	//평행사변형
	};

	meshes.emplace_back(std::make_shared<MeshData>(vertices,indices));
	shaders.emplace_back(std::make_shared<Shader>());
}
}