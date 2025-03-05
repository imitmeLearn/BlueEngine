#pragma once
#include "Mesh.h"

namespace Blue
{
class QuadMesh: public Mesh  //삼각형 메쉬 클래스
{
public:
	QuadMesh();

	void Update(float deltaTime);
	void Rotate(float angle);
private:
};
}