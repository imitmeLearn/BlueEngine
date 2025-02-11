#include <Windows.h>
#include <cmath>
#include "Vector2.h"

namespace Blue
{
const Vector2 Vector2::Zero = Vector2(0.f,0.f);
const Vector2 Vector2::One = Vector2(1.f,1.f);
const Vector2 Vector2::Right = Vector2(1.f,0.f);
const Vector2 Vector2::Up = Vector2(0.f,1.f);

std::wstring Vector2::ToString()
{
	wchar_t buffer[256];
	swprintf_s(buffer,256,TEXT("(%f,%f)"),x,y);

	return std::wstring();
}
float Vector2::Length()
{
	return sqrtf(x*x +y*y);
}
float Vector2::Dot()
{
	return 0.0f;
}
float Vector2::Dot(const Vector2& other)
{
	return (x*other.x)+ (y*other.y);
}
Vector2 Vector2::Normalized()
{
	float length = Length();
	return Vector2(x/length,y/length);
}
bool Vector2::Equals(const Vector2 & other)
{
	return x == other.x && y==other.y;	//float 오차발생할 수 있어서, 그 차가 특정 값 이하면, 절대 값 취해서, 오차범위 이내면 같다고 표현하다. 적당히 맞으니,엄밀히 어차범위 따져서, 작업을 해줘야 한다. 보통 구해서 쓰고, float 표준라이브러리에 있을 수 있는데, 부동 소수 어떻게 저장되는지,
}
}