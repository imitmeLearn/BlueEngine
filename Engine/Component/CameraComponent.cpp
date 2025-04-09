#include "CameraComponent.h"
#include "Core/Engine.h"
#include "Core\Common.h"
#include "Core/InputController.h"
#include "Math\Transform.h"
#include "Actor\Actor.h"

namespace Blue

{
CameraComponent::CameraComponent()
{
	//뷰 행렬 업데이트 및 바인딩.
	//data.viewMatrix =Matrix4::Translation(owner->transform.position * -1.f)
	//	* Matrix4::Transpose(Matrix4::Rotation(owner->transform.rotation));

		// 행렬 전치.
	data.viewMatrix = Matrix4::Transpose(data.viewMatrix);

	// 데이터 담아서 버퍼 생성.
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = sizeof(CameraBuffer);
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// 버퍼 데이터.
	D3D11_SUBRESOURCE_DATA bufferData = {};
	bufferData.pSysMem = &data;

	// 버퍼 생성.
	ID3D11Device& device = Engine::Get().Device();
	ThrowIfFailed(
		device.CreateBuffer(&bufferDesc,&bufferData,&cameraBuffer),
		TEXT("Failed to create camera buffer."));
}
void CameraComponent::Tick(float deltaTime)
{
	Component::Tick(deltaTime);

	if(!InputController::IsValid())
	{
		return;
	}

	static InputController& input = InputController::Get();

	//@Test 입력테스트 ('A')
	if(input.IsKeyDown(VK_ESCAPE))
	{
		//팝업 창 띄우기
		if(MessageBox(nullptr
			,TEXT("WANT TO QUIT?")
			,TEXT("QUIT ENGINE")
			,MB_YESNO)==IDYES)
		{
			Engine::Get().Quit();
		}
	}

	//카메라 이동 처리
	if(input.IsKey('A') || input.IsKey(VK_LEFT))
	{
		//왼쪽이동
		owner->transform.position.x -= 1.f*deltaTime;
	}

	if(input.IsKey('D') || input.IsKey(VK_RIGHT))
	{
		//오른쪽이동
		owner->transform.position.x += 1.f*deltaTime;
	}

	if(input.IsKey('W') || input.IsKey(VK_UP))
	{
		//위쪽이동
		owner->transform.position.y += 1.f*deltaTime;
	}

	if(input.IsKey('S') || input.IsKey(VK_DOWN))
	{
		//아래쪽이동
		owner->transform.position.y -= 1.f*deltaTime;
	}
}
void CameraComponent::Draw()
{
	Component::Draw();

	//뷰 행렬 업데이트 및 바인딩.
	data.viewMatrix =Matrix4::Translation(owner->transform.position * -1.f)
		* Matrix4::Transpose(Matrix4::Rotation(owner->transform.rotation));

	static ID3D11DeviceContext& context = Engine::Get().Context();

	// 전치 행렬 (CPU와 GPU가 행렬을 다루는 방식이 달라서).
	// 행기준 행렬을 열기준 행렬로 변환하기 위해 전치행렬 처리.
	data.viewMatrix = Matrix4::Transpose(data.viewMatrix);

	// 버퍼 업데이트.
	//context.UpdateSubresource(constantBuffer, 0, nullptr, &transformMatrix, 0, 0);
	D3D11_MAPPED_SUBRESOURCE resource = {};
	context.Map(cameraBuffer,0,D3D11_MAP_WRITE_DISCARD,0,&resource);
	memcpy(resource.pData,&data,sizeof(CameraBuffer));
	context.Unmap(cameraBuffer,0);

	// 버퍼 바인딩.
	context.VSSetConstantBuffers(1,1,&cameraBuffer);
}
}