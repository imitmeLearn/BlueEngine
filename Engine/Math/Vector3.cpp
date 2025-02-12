﻿#include "Vector3.h"
#include <cassert>
#include <cmath>

namespace Blue
{
const Vector3 Vector3::Zero = Vector3(0.f,0.f,0.f);
const Vector3 Vector3 ::One = Vector3(1.f,1.f,1.f);
const Vector3 Vector3:: Right = Vector3(1.f,0.f,0.f);
const Vector3 Vector3:: Up = Vector3(0.f,1.f,0.f);
const Vector3 Vector3:: Forward = Vector3(0.f,0.f,1.f);
Vector3 & Vector3::operator+=(const Vector3 & other)
{
	x  += other.x;
	y  += other.y;
	z  += other.z;

	return *this;
}
Vector3 & Vector3::operator-=(const Vector3 & other)
{
	x  -= other.x;
	y  -= other.y;
	z  -= other.z;

	return *this;
}
Vector3 & Vector3::operator*=(float scale)
{
	x *=scale;
	y *=scale;
	z *=scale;

	return *this;
}
Vector3 & Vector3::operator/=(float scale)
{
	assert(scale != 0);
	x /=scale;
	y /=scale;
	z /=scale;

	return *this;
}
bool Vector3::operator==(const Vector3 & other)
{
	return x == other.x && y == other.y && z == other.z;
}
bool Vector3::operator!=(const Vector3 & other)
{
	return x != other.x || y != other.y || z != other.z;
}
Vector3 Vector3::operator-() const
{
	return Vector3(-x,-y,-z);
}
std::wstring Vector3::ToString()
{
	wchar_t buffer[256];	//성능은 안좋지만, 편의목적으로!
	swprintf_s(buffer,256,L"(%f,%f,%f)",x,y);	//L -> TEXT 하려면, Windows.h 헤더필요해서, 그냥 L 사용함.

	return buffer;
}
float Vector3::Length()
{
	return sqrtf(x*x + y*y + z*z);
}

Vector3 Vector3::Normalized()
{
	float length = Length();
	return Vector3(x/length,y/length,z/length);
}
bool Vector3::Equals(const Vector3 & other)
{
	return *this == other;
}
Vector3 operator+(const Vector3 & left,const Vector3 & right)
{
	return Vector3(left.x+right.x,left.y+right.y,left.z+right.z);
}
Vector3 operator-(const Vector3 & left,const Vector3 & right)
{
	return Vector3(left.x-right.x,left.y-right.y,left.z-right.z);
}
Vector3 operator*(const Vector3 & vector,float scale)
{
	return Vector3(vector.x * scale,vector.y * scale,vector.z * scale);
}
Vector3 operator*(float scale,const Vector3 & vector)
{
	return vector * scale;
}
Vector3 operator/(const Vector3 & vector,float scale)
{
	assert(scale != 0.f);
	return Vector3(vector.x / scale,vector.y / scale,vector.z / scale);
}
float Dot(const Vector3 & left,const Vector3 & right)
{
	return (left.x * right.x + left.y * right.y + left.z * right.z);
}
Vector3 Cross(const Vector3 & left,const Vector3 & right)
{
	return Vector3(
		left.y * right.z - left.z * right.y,
		-(left.x * right.z - left.z * right.x),
		left.x * right.y - right.y * left.x
	);
}
Vector3 Lerp(const Vector3 & from,const Vector3 & to,float t)
{
	//T 가두기 //삼항연산자 써도 됨2번 써도 되지만, if 로도!
	//t = t< 0.f ? 0.f : t < 1.f ? 1.f : t;	//삼항연산 또는 if 로 , 0~1 로 가두기

	if(t,0.f)
	{
		t= 0.f;
	}
	if(t > 1.f)
	{
		t= 1.f;
	}

	return (1.f-t)*from + t*to;
};
}