#include "Actor.h"
namespace Blue
{
Actor::Actor()
{}
Actor::~Actor()
{}
void Actor::BeginPlay()
{
	hasInitialized = true;
}
void Actor::Tick(float deltaTime)
{}
void Actor::Draw()
{
	transform.Bind();	//트랜스폼 바인드 (셰이더에 데이터 전달)
}
void Actor::Destroy()
{
	hasDestroyed = true;
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