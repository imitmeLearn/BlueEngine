#pragma once
#include<vector>
#include<memory>
#include <d3d11.h>
#include "Vertex.h"
#include "../Core/Type.h"

#include"Math\Transform.h"
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
	//정점데이터 업데이트 하는 함수
	void UpdateVertexBuffer(const std::vector<Vertex>& vertices);

	std::vector<Vertex> vertices;	//정점데이터
	uint32 stride = 0;
	ID3D11Buffer* vertexBuffer = nullptr;

	std::vector<uint32> indices;	//인덱스 데이터
	ID3D11Buffer* indexBuffer= nullptr;
};
class Mesh
{
public:
	Mesh();
	virtual ~Mesh() =default;

	//virtual void Draw();

public:
	//@Temp : 임시 트랜스폼
	//Transform transform;
	//서브메시개수반환 getter
	uint32 SubMeshCount() const;
	//서브메시개수반환 getter
	std::weak_ptr<MeshData> GetSubMesh(int index) const;

protected:
	std::vector<std::weak_ptr<MeshData>> meshes;	//로더 만들었으니, 변경해주기 shared_ptr -> weak_ptr	//std::vector<std::shared_ptr<MeshData>> meshes;
	//std::vector<std::shared_ptr<class Shader>> shaders;
	//std::vector<std::weak_ptr<class Shader>> shaders;
};
}