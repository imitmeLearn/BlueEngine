#include "SphereMesh.h"
#include "Resource\ModelLoader.h"

namespace Blue
{
SphereMesh::SphereMesh()
{
	// 모델로더
	std::weak_ptr<MeshData> mesh;
	if(ModelLoader::Get().Load("Sphere.obj",mesh))
	{
		meshes.emplace_back(mesh);
	}
}
}