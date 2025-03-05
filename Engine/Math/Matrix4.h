#pragma once
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
	static Matrix4 Rotation(const Vector3& rotation);
	static Matrix4 Rotation(float x,float y,float z);
	static Matrix4 RotationX(float angle);
	static Matrix4 RotationY(float angle);
	static Matrix4 RotationZ(float angle);

	static Matrix4 Scale(const Vector3& scale);
	static Matrix4 Scale(float scale);
	static Matrix4 Scale(float x,float y,float z);

	//operator overloading
	Matrix4& operator= (const Matrix4& other);
	Matrix4& operator*(const Matrix4& other);
	Matrix4& operator*= (const Matrix4& other);

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