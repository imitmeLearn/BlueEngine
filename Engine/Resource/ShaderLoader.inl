//#include "ShaderLoader.h"	//임시로 추가한 것, 작성하는동안 오류나기에, 나중에 지울것

namespace Blue
{
//template<typename T,typename ...Args>
template<typename T,typename std::enable_if<std::is_base_of<Shader,T>:: value>::type* >
inline bool ShaderLoader::Load(std::weak_ptr<T>& outShader)
{
	auto name = typeid(T).name();	//typeid - 기본지정RTTI -
	auto find = shaders.find(name);
	if(find != shaders.end())
	{
		outShader = std::static_pointer_cast<T>(find->second);	//dynamic_pointer_cast 로 하는게 맞는데, 강제T 가 쉐이더의 자손이라는 강제를 할 예정이기에, static_pointer_cast 로 사용.
		return true;
	}

	//없으면 생성 후 관리자에 추가하고, 반환.
	std::shared_ptr<Shader> newShader = std::make_shared<T>();
	shaders.insert(std::make_pair(name,newShader));
	outShader = std::static_pointer_cast<T>(newShader);

	return true;
}
}