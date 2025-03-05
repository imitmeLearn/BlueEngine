#pragma once
#include <unordered_map>
#include<memory>
#include<typeinfo>
#include <string>

//스마트포인터 필요하니까, 메모리
//RTTI 도 할꺼니카, 타입인포
namespace Blue
{
class Shader;
class ShaderLoader	//싱글톤으로 만들거야.
{
public:
	ShaderLoader();
	~ShaderLoader() = default;

	template<typename T,typename... Args,typename std::enable_if<std::is_base_of<Shader,T>:: value>::type* = nullptr>	//가변파라미터
	bool Load(std::weak_ptr<T>& outShader,Args... args);

	static ShaderLoader& Get();
private:
	static ShaderLoader* instance;
	std::unordered_map<std::string,std::shared_ptr<Shader>> shaders;
};
}

#include "ShaderLoader.inl"	//인라인 헤더파일을 여기에 추가해준다.	//얘가 동작하려면,cpp 에 가서, 전방선언하거 #include "Shader/Shader.h"
//확장자는 컴파일에 안들어가는걸로 다 쓰면 됨, 명시적으로 inline 이라서, inl 을 사용한것.
