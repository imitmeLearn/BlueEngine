﻿#include "Matrix4.h"
#include <cmath>

#include "DirectXMath.h"
using namespace DirectX;

//#include "DirectXMathMatrix.h"
namespace Blue
{
Matrix4 Matrix4::Identity = Matrix4();
Matrix4::Matrix4()
{
	memset(elements,0,sizeof(float)*16);	// 원소elements 접근은, 변수가 편함.
	m00=m11=m22=m33=1.f;

	//XMmatrixrotation;	//라디안으로 변환해야 함.
}
Matrix4::Matrix4(const Matrix4 & other)
{
	memcpy(elements,other.elements,sizeof(float)*16);
}
Matrix4 Matrix4::Translation(const Vector3 & position)
{
	return Translation(position.x,position.y,position.z);
}
Matrix4 Matrix4::Translation(float x,float y,float z)
{
	Matrix4 m;
	//행렬
	m.m00 = 1.f;			m.m01 = 0.f;			m.m02 = 0.f;			m.m03 = 0.f;
	m.m10 = 0.f;			m.m11 = 1.f;			m.m12 = 0.f;			m.m13 = 0.f;
	m.m20 = 0.f;			m.m21 = 0.f;			m.m22 = 1.f;			m.m23 = 0.f;
	m.m30 = x	;			m.m31 = y	;			m.m32 = z	;			m.m33 = 1.f;
	return m;
}
Matrix4 Matrix4::Rotation(const Vector3 & rotation)
{
	return Rotation(rotation.x,rotation.y,rotation.z);
}
Matrix4 Matrix4::Rotation(float x,float y,float z)	//z 가 0이면, 짐벌락 안남.
{
	return RotationX(x) * RotationY(y) * RotationZ(z);
}
Matrix4 Matrix4::RotationX(float angle)
{
	Matrix4 m;	//반환을 위한 행렬 변수 선언(단위 행렬).

	float cosAngle = std::cos(angle*degreeToRadian);		//행렬 계산을 위한 삼각함수 값 저장.
	float sinAngle = std::sin(angle*degreeToRadian);		//행렬 계산을 위한 삼각함수 값 저장.

	//행렬
	m.m00 = 1.f;			m.m01 = 0.f;			m.m02 = 0.f;			m.m03 = 0.f;
	m.m10 = 0.f;			m.m11 = cosAngle;		m.m12 = sinAngle;		m.m13 = 0.f;
	m.m20 = 0.f;			m.m21 = -sinAngle;		m.m22 = cosAngle;		m.m23 = 0.f;
	m.m30 = 0.f;			m.m31 = 0.f;			m.m32 = 0.f;			m.m33 = 1.f;

	return m;
}

Matrix4 Matrix4::RotationY(float angle)	//두번째 요소를 안쓴다.
{
	Matrix4 m;	//반환을 위한 행렬 변수 선언(단위 행렬).

	float cosAngle = std::cos(angle*degreeToRadian);		//행렬 계산을 위한 삼각함수 값 저장.
	float sinAngle = std::sin(angle*degreeToRadian);		//행렬 계산을 위한 삼각함수 값 저장.

	//행렬
	m.m00 = cosAngle;		m.m01 = 0.f;			m.m02 = -sinAngle;		m.m03 = 0.f;
	m.m10 = 0.f;			m.m11 = 1.f;			m.m12 = 0.f;			m.m13 = 0.f;
	m.m20 = sinAngle;		m.m21 = 0.f;			m.m22 = cosAngle;		m.m23 = 0.f;
	m.m30 = 0.f;			m.m31 = 0.f;			m.m32 = 0.f;			m.m33 = 1.f;

	return m;
}
Matrix4 Matrix4::RotationZ(float angle)		//세번째 요소 안쓴다.
{
	Matrix4 m;	//반환을 위한 행렬 변수 선언(단위 행렬).

	float cosAngle = std::cos(angle*degreeToRadian);		//행렬 계산을 위한 삼각함수 값 저장.
	float sinAngle = std::sin(angle*degreeToRadian);		//행렬 계산을 위한 삼각함수 값 저장.

	//행렬
	m.m00 = cosAngle;		m.m01 = sinAngle;		m.m02 = 0.f;			m.m03 = 0.f;
	m.m10 = -sinAngle;		m.m11 = cosAngle;		m.m12 = 0.f;			m.m13 = 0.f;
	m.m20 = 0.f;			m.m21 = 0.f;			m.m32 = 0.f;			m.m33 = 1.f;

	return m;
}
Matrix4 Matrix4::Scale(const Vector3 & scale)
{
	return Scale(scale.x,scale.y,scale.z);
}
Matrix4 Matrix4::Scale(float scale)
{
	return Scale(scale,scale,scale);
}
Matrix4 Matrix4::Scale(float x,float y,float z)
{
	Matrix4 m;
	//행렬
	m.m00 = x;				m.m01 = 0.f;			m.m02 = 0.f;			m.m03 = 0.f;
	m.m10 = 0.f;			m.m11 = y;				m.m12 = 0.f;			m.m13 = 0.f;
	m.m20 = 0.f;			m.m21 = 0.f;			m.m22 = z;				m.m23 = 0.f;
	m.m30 = 0.f;			m.m31 = 0.f;			m.m32 = 0.f;			m.m33 = 1.f;
	return m;
}

Matrix4 Matrix4::Transpose(const Matrix4& target)
{
	Matrix4  m = target;

	std::swap(m.m01,m.m10);
	std::swap(m.m02,m.m20);
	std::swap(m.m03,m.m30);

	std::swap(m.m12,m.m21);
	std::swap(m.m13,m.m31);

	std::swap(m.m23,m.m32);

	return m;
}

Matrix4 Matrix4::Perspective(float fieldOfView,float width,float height,float nearDistance,float farDistance)
{
	//XMMatrixPerspectiveFovLH

	float aspect  = width / height;		//종횡비 (화면, 가로서로 비율)
	float fov = fieldOfView / 2.f * degreeToRadian;	//시야각 변환
	float h = 1.f / std::tanf(fov);	//초점거리D
	float w = h / aspect;
	float A = (nearDistance + farDistance) / (farDistance - nearDistance);
	float B = (-2.f * nearDistance * farDistance) / (farDistance - nearDistance);

	Matrix4 m;	//투영행렬
	m.m00 = w;				m.m01 = 0.f;				m.m02 = 0.f;			m.m03 = 0.f;
	m.m10 = 0.f;			m.m11 = h;					m.m12 = 0.f;			m.m13 = 0.f;
	m.m20 = 0.f;			m.m21 = 0.f;				m.m22 = A;				m.m23 = 1.f;
	m.m30 = 0.f;			m.m31 = 0.f;				m.m32 = B;				m.m33 = 0.f;

	return m;
}

Matrix4& Matrix4::operator=(const Matrix4& other)
{
	//Matrix4 m;	//반환을 위한 행렬 변수 선언(단위 행렬).
	memcpy(elements,other.elements,sizeof(float)*16);
	return *this;
}
Matrix4 Matrix4::operator*(const Matrix4& other)
{
	Matrix4 m;

	m.m00 =		m00 * other.m00 		+m01 *other.m10			+m02 *other.m20		+m03 *other.m30;
	m.m01 =		m00 * other.m01 		+m01 *other.m11			+m02 *other.m21		+m03 *other.m31;
	m.m02 =		m00 * other.m02 		+m01 *other.m12			+m02 *other.m22		+m03 *other.m32;
	m.m03 =		m00 * other.m03 		+m01 *other.m13			+m02 *other.m23		+m03 *other.m33;

	m.m10 =		m10 * other.m00 		+m11 *other.m10			+m12 *other.m20		+m13 *other.m30;
	m.m11 =		m10 * other.m01 		+m11 *other.m11			+m12 *other.m21		+m13 *other.m31;
	m.m12 =		m10 * other.m02 		+m11 *other.m12			+m12 *other.m22		+m13 *other.m32;
	m.m13 =		m10 * other.m03 		+m11 *other.m13			+m12 *other.m23		+m13 *other.m33;

	m.m20 =		m20 * other.m00 		+m21 *other.m10			+m22 *other.m20		+m23 *other.m30;
	m.m21 =		m20 * other.m01 		+m21 *other.m11			+m22 *other.m21		+m23 *other.m31;
	m.m22 =		m20 * other.m02 		+m21 *other.m12			+m22 *other.m22		+m23 *other.m32;
	m.m23 =		m20 * other.m03 		+m21 *other.m13			+m22 *other.m23		+m23 *other.m33;

	m.m30 =		m30 * other.m00 		+m31 *other.m10			+m32 *other.m20		+m33 *other.m30;
	m.m31 =		m30 * other.m01 		+m31 *other.m11			+m32 *other.m21		+m33 *other.m31;
	m.m32 =		m30 * other.m02 		+m31 *other.m12			+m32 *other.m22		+m33 *other.m32;
	m.m33 =		m30 * other.m03 		+m31 *other.m13			+m32 *other.m23		+m33 *other.m33;

	return m;
}
Matrix4  Matrix4::operator*=(const Matrix4& other)
{
	*this = *this * other;
	return *this;
}
//4번째 차수가 있다 == 이동, 스케일,회전은 값이 이미 0이기에, 영향을 안받고, 위치는 뒤가 1이기에, 해당 +1.f* matrix.m3* 부분이 계산된다. (곱셈의 항등원)-이동변환하려면, const Matrix4 & matrix 차수 맞춰서,더해주면, 된다.
Vector3 operator*(const Vector3 & vector,const Matrix4 & matrix)
{
	Vector3 result;
	result.x = vector.x * matrix.m00		+ vector.y * matrix.m10			+ vector.z * matrix.m20		+1.f* matrix.m30;
	result.y = vector.x * matrix.m01		+ vector.y * matrix.m11			+ vector.z * matrix.m21		+1.f* matrix.m31;
	result.z = vector.x * matrix.m02		+ vector.y * matrix.m12			+ vector.z * matrix.m22		+1.f* matrix.m32;
	return result;
}
Vector3 operator*(const Matrix4 & matrix,const Vector3 & vector)
{
	return vector * matrix;
}
}