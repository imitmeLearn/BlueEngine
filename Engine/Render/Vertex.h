#pragma once
#include "Math//Vector3.h"
#include "Math//Vector2.h"	//c++ >일반 > 추가포함디렉터리 : $(ProjectDir)\; 작성해 넣어서, ../ 안써도 됨.
namespace Blue
{
class Vertex
{
public:
	~Vertex()=default;

	Vertex(const Vector3& position,const Vector3& color,const Vector2& texCoord)
		:position(position),color(color),texCoord(texCoord)
	{}//4*8 =32 가 Stride 에서 넘어올거야

	Vertex(const Vector3& position)
		:position(position)
	{}
	Vertex(const Vector3& position,const Vector3& color)
		:position(position),color(color)
	{}
	static unsigned int Stride()
	{
		return sizeof(Vertex);
	}

private:

public:
	Vector3 position;
	Vector3 color;
	Vector2 texCoord;	//정점 기준 텍스쳐 좌표//3차원도 있찌만, 잘 안씀.
};
}