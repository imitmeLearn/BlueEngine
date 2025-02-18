#pragma once
#include "../Math//Vector3.h"
namespace Blue
{
class Vertex
{
public:
	~Vertex()=default;
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
};
}