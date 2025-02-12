#pragma once

#include "../Core/Type.h"
#include <string>

namespace Blue
{
class Vector3
{
public:
	float x= 0.f;
	float y= 0.f;
	float z= 0.f;

	Vector3(float value)
		:x(value),y(value),z(value)
	{}
	Vector3(float x=0.f,float y = 0.f,float z=0.f)
		:x(x),y(y),z(z)
	{}

	//기본값.//전역변수이기에. 클래스 선언될 떄, 초기화 되어서, 바로 읽어서, 쓸 쑤 있다.
	static const Vector3 Zero;
	static const Vector3 One;
	static const Vector3 Right;
	static const Vector3 Up;
	static const Vector3 Forward;

	//메모리 크기 (Stride
	//static unsigned int Stride()
	static uint32  Stride() //#include "../Core/Type.h" 해서, unsigned -> uint32
	{
		return sizeof(Vector3);
	}

	//연산자 오버로딩
	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);
	Vector3& operator*=(float scale);
	Vector3& operator/=(float scale);
	bool operator==(const Vector3& other);
	bool operator!=(const Vector3& other);
	Vector3 operator-() const;

	friend Vector3 operator+(const Vector3& left,const Vector3& right);
	friend Vector3 operator-(const Vector3& left,const Vector3& right);
	friend Vector3 operator*(const Vector3& vector,float scale);
	friend Vector3 operator*(float scale,const Vector3& vector);
	friend Vector3 operator/(const Vector3& vector,float scale);

	////(x, y)문자열로 제공해 만들어주는.... 문자열 생성 함수.
	std::wstring ToString();

	//길이 구하기
	float Length();
	//내적
	friend 	float Dot(const Vector3& left,const Vector3& right);
	//외적 X
	friend 	Vector3 Cross(const Vector3& left,const Vector3& right);
	Vector3 Normalized();
	bool Equals(const Vector3& other);

	//선형보간 (Lerp - Linear Interpolation)
	//- 외워야 하는것 =(1.f-t)*from + t*to
	friend Vector3 Lerp(const Vector3& from,const Vector3& to,float t);
};
}