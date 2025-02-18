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

	//리소스 생성 - 버텍스
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.ByteWidth = stride*(uint32)vertices.size();
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; //필수

	D3D11_SUBRESOURCE_DATA vertexData = {};	//정점 데이터 //여러데이터, 하나로 넣을 떄 사용
	vertexData.pSysMem =	vertices.data();

	//장치 얻어오기
	ID3D11Device& device = Engine::Get().Device();

	//(정점)버퍼 생성
	auto result= device.CreateBuffer(&vertexBufferDesc,&vertexData,&vertexBuffer);		//버퍼(Buffer) 메모리 덩어리 - 버텍스
	if(FAILED(result))	//결과 확인
	{
		MessageBoxA(nullptr,"fail to CreateBuffer - vertex  ","ERROR",MB_OK);
		__debugbreak();
	}

	//리소스 생성 - 인덱스
	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.ByteWidth = sizeof(int)  * indices.size();
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER; //필수

	D3D11_SUBRESOURCE_DATA indexData = {};	//정점 데이터 //여러데이터, 하나로 넣을 떄 사용
	indexData.pSysMem =	indices.data();

	auto	result=	device.CreateBuffer(&indexBufferDesc,&indexData,&indexBuffer);	//버퍼(Buffer) 메모리 덩어리  - 인덱스
	if(FAILED(result))	//결과 확인
	{
		MessageBoxA(nullptr,"fail to CreateBuffer -index ","ERROR",MB_OK);
		__debugbreak();
	}
}
void MeshData::Bind()
{}
}