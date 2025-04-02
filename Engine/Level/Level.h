#pragma once
#include <vector>
#include <memory>
#include "Core\Type.h"

namespace Blue{
class Actor;	//전방선언

class Level	//월드 배치한 액터 관리하는 것이 레벨
{
public:
	Level();
	virtual	~Level();
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	void AddActor(std::shared_ptr<Actor> newActor);

	std::shared_ptr<Actor> GetActor(int index) const;
	const uint32 ActorCount() const;

	std::shared_ptr<Actor> GetCamera() const;

protected:
	std::vector<std::shared_ptr<Actor>> actors;
	std::shared_ptr<Actor> cameraActor;		//메인 카메라 엑터
private:
};
}