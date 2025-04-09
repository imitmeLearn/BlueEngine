﻿#pragma once
#include "Core\Type.h"
#include "Vector3.h"
namespace Blue
{
class Matrix4
{
public:
	Matrix4();
	Matrix4(const Matrix4& other);//복사생성자
	~Matrix4() = default;

	//메모리 너비(단위:바이트)
	static uint32 Stride()
	{
		return sizeof(Matrix4);
	}
	//이동 변환 행렬 (T)
	static Matrix4 Translation(const Vector3& position);
	static Matrix4 Translation(float x,float y,float z);

	//회전 변환 행렬 (R)
	static Matrix4 Rotation(const Vector3& rotation);
	static Matrix4 Rotation(float x,float y,float z);
	static Matrix4 RotationX(float angle);
	static Matrix4 RotationY(float angle);
	static Matrix4 RotationZ(float angle);

	//크기 변환 행렬 (S)
	static Matrix4 Scale(const Vector3& scale);
	static Matrix4 Scale(float scale);
	static Matrix4 Scale(float x,float y,float z);

	//전치 행렬 //앞이랑 뒤 같은면 바꾼다? //직교인 경우, 역행렬과 같다.기저베터들은 직교니, 전치행렬 바꾸면, 역행렬이 돼,카메라 행렬만들때, 반대 변환 행렬을 만들어, DX 는 행기준(또는 우선) 행렬,
	static Matrix4 Transpose(const Matrix4& target);

	//원근투영
	static Matrix4 Perspective(
		float fieldOfView	//시야각
		,float width	//종횡비 화면 너비
		,float height	//종횡비 화면 높이
		,float nearDistance		//화면에 그려질 수 있는 가장 가까운 거리
		,float farDistance		//화면에 그려질 수 있는 가장 먼 거리
	);	//t시이갹.

	//operator overloading
	Matrix4& operator= (const Matrix4& other);
	Matrix4 operator*(const Matrix4& other);
	Matrix4 operator*= (const Matrix4& other);

	friend Vector3 operator* (const Vector3& vector,const Matrix4& matrix);
	friend Vector3 operator* (const Matrix4& matrix,const Vector3& vector);

	static Matrix4 Identity;
	//Degree <->Radian  constexpr를 쓰면, 부를때마다, 컴파일시점에 계산된 결과만 저장해 둔다. !!!!!
	static constexpr float degreeToRadian = 3.141592f / 180.f;
	static constexpr float radiantoDegree = 180.f / 3.141592f ;

private:
	union //공용체 : 메모리를 공유한다. //덩치큰것을 기준으로 만들고, 둘이 같은거!	//메모리구조는 1자로 잡힘.
	{
		struct
		{
			float m00,m01,m02,m03;
			float m10,m11,m12,m13;
			float m20,m21,m22,m23;
			float m30,m31,m32,m33;
		};
		float elements[4*4];
	};
};
}