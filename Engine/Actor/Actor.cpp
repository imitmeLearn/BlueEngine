#include "Actor.h"
#include "Component/Component.h"
namespace Blue
{
Actor::Actor()
{}
Actor::~Actor()
{}
void Actor::BeginPlay()
{
	if(hasInitialized)
	{
		return;
	}	//예외처림
	hasInitialized = true;
	for(const auto& component : components)
	{
		component->BeginPlay();
	}	//컴포넌트 함수 호출
}
void Actor::Tick(float deltaTime)
{
	if(!IsActive())
	{
		return;
	}	//예외처리
	for(const auto& component : components)
	{
		component->Tick(deltaTime);
	}	//컴포넌트 함수 호출
}
void Actor::Draw()
{
	if(!IsActive())
	{
		return;
	}	//예외처리
	transform.Bind();	//트랜스폼 바인드 (셰이더에 데이터 전달)
	for(const auto& component : components)
	{
		component->Draw();
	}	//컴포넌트 함수 호출
}
void Actor::Destroy()
{
	hasDestroyed = true;
}
void Actor::AddComponent(std::shared_ptr<class Component> newComponent)
{
	components.emplace_back(newComponent); //컴포넌트 배열에 새로운 컴포넌트 추가
	newComponent->SetOwner(this);	//컴포넌트 소유 설정
}
const bool Actor::IsActive() const
{
	return isActive && !hasDestroyed;
}
const bool Actor::HasInitialized() const
{
	return hasInitialized;
}
}