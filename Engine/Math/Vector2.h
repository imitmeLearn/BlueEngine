#pragma once
#include <string>
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
	{}

	//기본값.//전역변수이기에. 클래스 선언될 떄, 초기화 되어서, 바로 읽어서, 쓸 쑤 있다.
	static const Vector2 Zero;
	static const Vector2 One;
	static const Vector2 Right;
	static const Vector2 Up;

	////(x, y)문자열로 제공해 만들어주는.... 문자열 생성 함수.
	std::wstring ToString();

	//길이 구하기
	float Length();
	//float LengthSquared();
	float Dot();
	float Dot(const Vector2& other);
	Vector2 Normalized();
	bool Equals(const Vector2& other);
};
}