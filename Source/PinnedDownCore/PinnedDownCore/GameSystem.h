#pragma once

#include <memory>

namespace PinnedDownCore
{
	class Game;

	class GameSystem
	{
	public:
		virtual void InitSystem(Game* game)
		{
			this->game = game;
		}

		virtual void Update(float dt) {}
		virtual void Render() {}

	protected:
		Game* game;
	};
}