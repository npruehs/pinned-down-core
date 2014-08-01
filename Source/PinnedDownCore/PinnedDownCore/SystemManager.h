#pragma once

#include <vector>
#include <memory>
#include "GameSystem.h"

namespace PinnedDownCore
{
	class Game;

	class SystemManager
	{
	public:
		SystemManager(Game* game);

		void AddSystem(GameSystem* system);
		void InitSystems();
		void Update(float dt);
		void Render();

	private:
		Game* game;
		std::vector<std::shared_ptr<GameSystem>> systems;
	};
}