#include<Windows.h>
#include<winerror.h>
#include "Core/Window.h"
#include "render/renderer.h"
#include "Core/Engine.h"

/*
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);	//원본
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);	//가능//사용하는거
LRESULT  WindowProc(HWND, UINT, WPARAM, LPARAM);		//가능
*/

//WINAPI는 define 이야, stdcall cdecl(함수호출규약) 있는데, 스택에 올라갈때, 스택 어떻게 쓸지 규약이 있어.크게 나누면, 사용자 함수랑 시스템 함수 있어 스택잡히는것이 피라미터 잡히는거 반대야
//시스템함수이기에, 앞에 붙여주는거야, 안붙이면, 기본값을 붙여, stdcall, 안붙이면, cdecl 사용자함수로,
//_In_opt_  _In_ 는 안붙여도 되지만, 때고나서 빌드하면, 초록줄로 경고(주석일치않는다고....) 있을거야!옵션처리값이다.붙여도 안붙여도 되긴하다.기억안나면, msdn winmain 검색해서, 보면돼,
//stdcall clrcall 같은거야.한바이트
/*
LPSTR 가보면, char* 야, 해서, LPSTR 대신  char* 써도 된다. 왜 LPSTR냐면, 옛날에? 대문자로 변수할거야 했었기에, Long? Pointer STring 야.

HINSTANCE 는
DECLARE_HANDLE

hInstance는 WinMain 는 창 제어 포인터, 창은, 윈도우즈 운영체제 입장에서 소중한 리소스, 시스템이 관리하는, 생성 부탁하고 제어 메모리르 받는데, 그게, H Instance 야. 프로그램 메모리 주소 생성해서, hInstance에 넣어줌.
hPrevInstance 는 안쓴지 오래됨, 3.1 버전?? 95, 98
_In_ LPSTR lpCmdLine,는
창모드 끌 때, 옵션값이다. 실행할땐 안써. command 에서 실행할 일 없기에,

과장해서 말하면, WinMain은 hInstance 하나 쓰려고 쓰는거야!!!!!!!!!

'msdn 창 만들기' 검색하면,https://learn.microsoft.com/ko-kr/windows/win32/learnwin32/creating-a-window
WNDClass 만들어서, 창 생성하는거 나오는데,. 복사해
*/

using namespace Blue;
#pragma region 창 모드로 할 때 메인 함수(Entry Point)
////창 모드로 할 때 메인 함수(Entry Point)
//int WINAPI WinMain(
//	_In_ HINSTANCE hInstance,
//	_In_opt_ HINSTANCE hPrevInstance,
//	_In_ LPSTR lpCmdLine,
//	_In_ int nShowCmd
//)
//{
//	Engine engine (1280,900,TEXT("ENGINE DEMO"),hInstance);		//엔진 생성
//	engine.Run();												//엔진 실행
//
//	return 0;
//}
#pragma endregion

#include <iostream>
#include "Math/Vector2.h"
#include <Core\Common.h>
#include<typeinfo>
#include <Shader\Shader.h>
#include <Shader\TextureMappingShader.h>

template<typename T,typename std::enable_if<std::is_base_of<Shader,T>:: value>::type* = nullptr>
void TestClass(){
	std::boolalpha(std::cout);	//함수찍거나, 클래스, 찍는 트리.
	std::cout<<"s -" <<	typeid(T).name() << "\n";
	//std::cout<<	typeid(Blue::Engine).name() << "\n";
	std::cout<<	std::is_base_of<Shader,T>::value << "- e\n";
	//std::cout<<	std::is_base_of<Shader,TextureMappingShader>::value << "\n";
	//std::cout<<	std::is_base_of<Shader,Engine>::value << "\n";
}
/*
* TodoList.
* - Input Controller (Window Message Process)
* - Actor (Entity, GameObject) / Component / Scene - level
* - FBX Loader. (Assimp / FBX SDK -> Submesh)
* - Camera (View / Projection - Perspective, Othographic)
*	Screen Coordinate System (NDC - Normalized Device Coordinates).
* - Shade (Shader) - Light / Brightness / Darkness
*	Ambient (Static/GI) / Diffuse (Lambart .../Roughness) / Specular (Highlight, Phong, Blinn-Phong, Metalic).
* - Normal Mapping.
* - Render Target (Draw to Texture).
* - Shadow Mapping(Shadow Map)
* - Environment Mapping (Sky Sphere(Box))
* = Tone Mapping.
*
* - Skeletal Mesh (Skinned Mesh) - skeleton.
*	Skeletal Mesh Animation.
* = Physics
*/

/* 렌더링 파이프라인? 그래픽스 파이브라인: 정점 변환 잘하고, 픽셀 칠 잘하는~~
* IA 입력 정리 > VS 정점쉐이터...(Option) > RS/보간기 : 보간기가 선형보간하고,:  > PS 픽셀 쉐이더 :  >  OM 출력조립
* vs 정점 쉐이더 : 정점 변환, 객체 월드 뷰 투영 좌표계로 변경하는 단계 ,  Skeletal Mesh 도 정점쉐이더 -> 메모리 많이 먹어, 가상뼈대심어 정점변환공식만들어서 사용하는것! 해서, staticmesh 랑 값다름.
*		파라메타뽑아보면, ...?? 정점처리 후, 단위는 픽셀 - 뼈대 없음. 애니메이션 후, 모델링 픽셀로 나오니,
* ps 픽셀 쉐이더 : 조명처리가 주요 목적이다. 정점 잘 넘어 왔으면, 추가로 입력받아서 조명처리하는것, pbr diffuse specular 등을 여기서 하는것. ***그래픽스의 꽃?!
* 엔진 개발자 - 렌더러 개발자 : 렌더러 다 만들어서 사용하던 추세.; -> * 렌더링 파이프라인 이해하면 좋겠따다는 분들
*
*/

int main()
{
	TestClass<TextureMappingShader>();
	//TestClass<Engine>();	//템플릿 인스턴스 없어서, 빨간줄...억지로 만들려고 함녀 문제되는...//타입잘못지정하면, 에러나니, 인지할 수 있음

	std::boolalpha(std::cout);	//함수찍거나, 클래스, 찍는 트리.
	std::cout<<"1.typeid(Engine).name()  : "	<<typeid(Engine).name() << "\n";
	std::cout<<"2.typeid(Blue::Engine).name() : "<<	typeid(Blue::Engine).name() << "\n";
	std::cout<<	std::is_base_of<Shader,TextureMappingShader>::value << "\n";
	std::cout<<	std::is_base_of<Shader,Engine>::value << "\n";

	//매크로 되는지 테스트
	//ThrowIfFailed(E_FAIL,TEXT("Text Error"));

//	std::cout<< "테스트 - 디버깅 가능해" <<"\n";
	Engine engine (1280,800,TEXT("Engine DEMO"),GetModuleHandle(nullptr));
	engine.Run();

	//std::cout<< "Vector2 테스트" <<"\n";	//콘솔창에!
	//OutputDebugStringA("테스트!!!!!!!!!!!\n"); //출력창에!
}