﻿#pragma once
#include "Vector3.h"
#include "Matrix4.h"
#include <d3d11.h>

namespace Blue
{
class Transform
{
public:
	Transform();
	~Transform();
	void Bind();
	void Tick();
public:
	Vector3 position = Vector3::Zero;	//트랜스폼(변환) 요소 (TRS)
	Vector3 rotation = Vector3::Zero;	//트랜스폼(변환) 요소 (TRS)
	Vector3 scale = Vector3::One;		//트랜스폼(변환) 요소 (TRS)
private:
	Matrix4 transformMatrix;				//트랜스폼 행렬
	ID3D11Buffer* constantBuffer = nullptr;	//상수 버퍼
};
}