#pragma once
#include "Component.h"
#include "Math\Matrix4.h"
#include <d3d11.h>
namespace Blue
{
struct CameraBuffer	//카메라 버퍼 (상수버퍼)
{
	Matrix4 viewMatrix;	//뷰 변환 행렬	//데이터 담아서, 쉐이더에 보내야 함.
	//투영변환 행열
	Matrix4 projectionMatrix;

	Vector3 cameraPosition;//카메라 위치 //쉐이더와 일치해야 함.
	float padding;	//패딩	//쉐이더와 일치해야 함.
};
class CameraComponent: public Component
{
public:
	CameraComponent();
	~CameraComponent() = default;
	virtual void Tick(float deltaTime) override;
	virtual void Draw () override;

private:

	CameraBuffer data;	//카메라 속성
	ID3D11Buffer* cameraBuffer = nullptr;	//DX Buffer.
};
}