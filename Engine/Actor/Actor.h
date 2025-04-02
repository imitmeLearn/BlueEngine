#pragma once
#include <string>
#include <Math\Transform.h> //설계 시 고려할 사항.

namespace Blue
{
class Actor
{
public:
	Actor();
	virtual ~Actor(); //기반클래스 여서, virtual
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Draw();
	void Destroy();
	const bool IsActive() const;
	const bool HasInitialized() const;
public:
	Transform transform; //스택변수 //엑터의 TRS 관리하는 트랜스폼. 변환정보
private:
protected:
	std::wstring name = TEXT("Actor");	//액터 이름. 일반적으로 Hash 로 변환해서 사용함.
	bool hasInitialized = false; //액터 초기화 여부.
	bool isActive = false;		//활성화와 여부
	bool hasDestroyed = false;	//삭제 여부
};
}
