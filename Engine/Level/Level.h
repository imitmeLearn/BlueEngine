#pragma once
#include <vector>
#include <memory>

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

protected:
	std::vector<std::shared_ptr<Actor>> actors;
private:
};
}