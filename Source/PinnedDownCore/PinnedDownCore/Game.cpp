#include "Game.h"

using namespace PinnedDownCore;

Game::Game() :
	eventManager(std::unique_ptr<EventManager>(new EventManager())),
	entityManager(std::unique_ptr<EntityManager>(new EntityManager(this))),
	systemManager(std::unique_ptr<SystemManager>(new SystemManager(this)))
{
}

void Game::Update(float dt)
{
	this->systemManager->Update(dt);
	this->eventManager->Tick();
	this->entityManager->CleanUpEntities();
	this->eventManager->Tick();

	if (this->logger != nullptr)
	{
		this->logger->Flush();
	}
}
