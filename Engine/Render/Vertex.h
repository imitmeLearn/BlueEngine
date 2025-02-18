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
	static unsigned int Stride()
	{
		return sizeof(Vertex);
	}

private:

public:
	Vector3 position;
};
}