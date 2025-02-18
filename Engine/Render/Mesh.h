#pragma once
#include<vector>
#include <d3d11.h>
#include "Vertex.h"
#include "../Core/Type.h"
namespace Blue
{
struct  MeshData	//메쉬 데이터 구조체.
{
	~MeshData();
	MeshData();
	MeshData(
	const std::vector<Vertex>& vertices,
	const std::vector<uint32>& indices
	);

	void Bind();
	uint32 IndexCount() const
	{
		return (uint32)indices.size();
	}

	std::vector<Vertex> vertices;	//정점데이터
	uint32 stride = 0;
	ID3D11Buffer* vertexBuffer = nullptr;

	std::vector<uint32> indices;	//인덱스 데이터
	ID3D11Buffer* indexBuffer= nullptr;
};
class Mesh
{};
}