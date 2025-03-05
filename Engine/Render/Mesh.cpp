#include "Mesh.h"
#include "../Core/Engine.h"
#include "../Shader/Shader.h"

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

	result=	device.CreateBuffer(&indexBufferDesc,&indexData,&indexBuffer);	//버퍼(Buffer) 메모리 덩어리  - 인덱스
	if(FAILED(result))	//결과 확인
	{
		MessageBoxA(nullptr,"fail to CreateBuffer -index ","ERROR",MB_OK);
		__debugbreak();
	}
}
void MeshData::Bind()
{
	//컨텍스트 얻어오기
	static ID3D11DeviceContext& context = Engine::Get().Context();

	//정점/ 인덱스 버퍼 바인딩.
	static uint32 offset = 0;
	context.IASetVertexBuffers(0,1,&vertexBuffer,&stride,&offset);
	context.IASetIndexBuffer(indexBuffer,DXGI_FORMAT_R32_UINT,0);
}
Mesh::Mesh()
{}
void Mesh::Draw()
{
	//컨텍스트 얻어오기.
	ID3D11DeviceContext& context = Engine::Get().Context();

	//루프 순회하면서, 바인딩 & 드로우.
	for(int ix = 0; ix < (int32)meshes.size(); ix++)
	{
		meshes[ix]->Bind();
		shaders[ix].lock()->Bind();	//소유권이 없어서, 포인터를 읽어오는 함수 lock , - 없으면 null, 있으면, sharedptr 반환된다.
		//auto shader = shaders[ix].lock();
		//if(!shader)
		//{
		//	continue;	//물체가 여러개면, ...쉐이더 바인드 안하면, 오류내고, 다른물체 그렸는데, 반환 안되면, 전에 그린거 쓰임. 해서, 쉐이더 쓰고나서 reset 해주고, 찌꺼기 비워주는 작업해줘야 한다.
		//	//실패할 수 있기때문에, lock 사용
		//  // 리소스 매니저가 나중에 죽으니, 쉐이더 없어지는 경우, 간혹 있는데, 곧이어서, DX 오류가 날것임.
		//	//정상인데 lock 걸리면, 내 문제.
		//}

		context.DrawIndexed(meshes[ix]->IndexCount(),0,0);
	}
}
}