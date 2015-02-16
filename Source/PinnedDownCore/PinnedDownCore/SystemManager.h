#pragma once

#include <vector>
#include <memory>
#include "GameSystem.h"

typedef std::shared_ptr<PinnedDownCore::GameSystem> SystemPtr;

namespace PinnedDownCore
{
	class Game;

	class SystemManager
	{
	public:
		SystemManager(Game* game);

		void AddSystem(const SystemPtr & system);
		void InitSystems();
		void Update(float dt);
		void Render();

	private:
		Game* game;
		std::vector<SystemPtr> systems;
	};
}