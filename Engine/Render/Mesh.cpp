#include "Mesh.h"
#include "../Core/Engine.h"

namespace Blue
{
MeshData::~MeshData()
{
	//리소스 해제.
	if(vertexBuffer)
	{
		vertexBuffer->Release();
	}if(indexBuffer)
	{
		indexBuffer->Release();
	}
}
MeshData::MeshData()
{}
MeshData::MeshData(
	const std::vector<Vertex>& vertices,
	const std::vector<uint32>& indices)
{
	//파라미터 복사.
	this->vertices.assign(vertices.begin(),vertices.end());
	stride = Vertex::Stride();
	this->indices.assign(indices.begin(),indices.end());
}
void MeshData::Bind()
{}
}