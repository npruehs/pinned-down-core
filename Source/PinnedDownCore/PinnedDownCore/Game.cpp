#include "Game.h"

using namespace PinnedDownCore;

Game::Game()
{
	this->eventManager = std::unique_ptr<EventManager>(new EventManager());
	this->entityManager = std::unique_ptr<EntityManager>(new EntityManager(this));
	this->systemManager = std::unique_ptr<SystemManager>(new SystemManager(this));
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
