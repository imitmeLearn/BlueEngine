#pragma once
#include <string>
#include <vector>
#include <memory>//스마트포인터
#include <Math\Transform.h> //설계 시 고려할 사항.
namespace Blue
{
class Actor
{
	friend class Renderer;
public:
	Actor();
	virtual ~Actor(); //기반클래스 여서, virtual
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Draw();
	void Destroy();
	void AddComponent(std::shared_ptr<class Component> newComponent);	//컴포넌트 추가함수
	const bool IsActive() const;
	const bool HasInitialized() const;

public:
	Transform transform; //스택변수 //엑터의 TRS 관리하는 트랜스폼. 변환정보
private:
protected:
	std::wstring name = TEXT("Actor");	//액터 이름. 일반적으로 Hash 로 변환해서 사용함.
	bool hasInitialized = false; //액터 초기화 여부.
	bool isActive = true;		//활성화와 여부
	bool hasDestroyed = false;	//삭제 여부
	std::vector<std::shared_ptr<class Component>> components;	//컴포넌트 배열 //동적배열 - 필요에 따라 크기 늘려서, 추가 사용할 예정.
};
}
