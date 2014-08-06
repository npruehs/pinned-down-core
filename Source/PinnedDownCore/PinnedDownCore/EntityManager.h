#pragma once

#include <map>
#include <set>
#include <memory>
#include "IEntityComponent.h"

typedef unsigned int Entity;

#define INVALID_ENTITY_ID 0

typedef std::shared_ptr<PinnedDownCore::IEntityComponent> ComponentPtr;
typedef std::map<Entity, ComponentPtr> ComponentMap;

namespace PinnedDownCore
{
	class Game;

	class EntityManager
	{
	public:
		EntityManager(Game* game);

		Entity CreateEntity();
		void RemoveEntity(Entity entity);

		void AddComponent(Entity entity, ComponentPtr const & component);
		ComponentPtr GetComponent(Entity entity, HashedString componentType);

		template <class T> std::shared_ptr<T> GetComponent(Entity entity, HashedString componentType)
		{
			ComponentPtr p = this->GetComponent(entity, componentType);
			return std::static_pointer_cast<T>(p);
		}

		void CleanUpEntities();

	private:
		Game* game;

		// Maps that are mapping entity ids to specific components.
		std::map<Entity, ComponentMap> componentMaps;

		// Ids of all entities that have been removed in this tick.
		std::set<Entity> removedEntities;

		// Id that will be assigned to the next entity created.
		Entity nextEntity;
	};
}
