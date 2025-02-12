﻿#pragma once
#include <string>
#include "../Core/Type.h"
#include <iostream>
namespace Blue
{
class Vector2
{
public:
	union
	{
		struct
		{
			float x ;
			float y ;
		};
		float data[2];
	};

	Vector2()
		: x(x),y(y)
	{}

	Vector2(float value)
		: x(value),y(value)
	{}
	Vector2(float x,float y)
		: x(x),y(y)
	{
		std::cout<<"벡터 생성"<< x << ", " << y << "\n" ;
	}

	//기본값.//전역변수이기에. 클래스 선언될 떄, 초기화 되어서, 바로 읽어서, 쓸 쑤 있다.
	static const Vector2 Zero;
	static const Vector2 One;
	static const Vector2 Right;
	static const Vector2 Up;

	//메모리 크기 (Stride
	//static unsigned int Stride()
	static uint32  Stride() //#include "../Core/Type.h" 해서, unsigned -> uint32
	{
		return sizeof(Vector2);
	}

	//연산자 오버로딩
	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2& operator*=(float scale);
	Vector2& operator/=(float scale);
	bool operator==(const Vector2& other);
	bool operator!=(const Vector2& other);
	Vector2 operator-() const;

	friend Vector2 operator+(const Vector2& left,const Vector2& right);
	friend Vector2 operator-(const Vector2& left,const Vector2& right);
	friend Vector2 operator*(const Vector2& vector,float scale);
	friend Vector2 operator*(float scale,const Vector2& vector);
	friend Vector2 operator/(const Vector2& vector,float scale);

	////(x, y)문자열로 제공해 만들어주는.... 문자열 생성 함수.
	std::wstring ToString();

	//길이 구하기
	float Length();
	//float LengthSquared();
	float Dot();
	float Dot(const Vector2& other);
	friend 	float Dot(const Vector2& left,const Vector2& right);
	Vector2 Normalized();
	bool Equals(const Vector2& other);

	//선형보간 (Lerp - Linear Interpolation)
	//- 외워야 하는것 =
	friend Vector2 Lerp(const Vector2& from,const Vector2& to,float t);
};
}