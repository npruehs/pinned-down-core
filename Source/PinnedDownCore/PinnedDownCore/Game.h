#pragma once

#include <memory>

#include "EventManager.h"
#include "SystemManager.h"
#include "EntityManager.h"
#include "Logger.h"
#include "ResourceManager.h"

namespace PinnedDownCore
{
	class Game
	{
	public:
		Game();

		std::unique_ptr<EventManager> eventManager;
		std::unique_ptr<SystemManager> systemManager;
		std::unique_ptr<EntityManager> entityManager;
		std::unique_ptr<Logger> logger;
		std::unique_ptr<ResourceManager> resourceManager;

		void Update(float dt);
	};
}