#include "QuadMesh.h"
#include "Shader/Shader.h"
#include "Shader/TextureMappingShader.h"
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

	meshes.emplace_back(std::make_shared<MeshData>(vertices,indices));
	//shaders.emplace_back(std::make_shared<Shader>());	//텍스처 추가했기에, 그대로 하면, 검정화면 나옴.
	shaders.emplace_back(std::make_shared<TextureMappingShader>("T_coord.png"));
}
}