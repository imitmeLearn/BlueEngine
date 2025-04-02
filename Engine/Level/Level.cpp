#include "Level.h"
#include "Actor\Actor.h"
namespace Blue
{
Level::Level()
{}
Level::~Level()
{}
void Level::BeginPlay()
{
	for(const auto& actor : actors)
	{
		actor->BeginPlay();
	}
}
void Level::Tick(float deltaTime)
{
	for(const auto& actor : actors)
	{
		actor->Tick(deltaTime);
	}
}
void Level::AddActor(std::shared_ptr<Actor> newActor)
{
	actors.emplace_back(newActor);
}
}