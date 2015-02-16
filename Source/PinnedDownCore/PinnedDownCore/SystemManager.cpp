#include "Game.h"
#include "SystemManager.h"

using namespace PinnedDownCore;

SystemManager::SystemManager(Game* game)
{
	this->game = game;
}

void SystemManager::AddSystem(const SystemPtr & system)
{
	systems.push_back(system);
}

void SystemManager::InitSystems()
{
	for (unsigned int i = 0; i < systems.size(); i++)
	{
		systems[i]->InitSystem(this->game);
	}
}

void SystemManager::Update(float dt)
{
	for (unsigned int i = 0; i < systems.size(); i++)
	{
		systems[i]->Update(dt);
	}
}

void SystemManager::Render()
{
	for (unsigned int i = 0; i < systems.size(); i++)
	{
		systems[i]->Render();
	}
}
